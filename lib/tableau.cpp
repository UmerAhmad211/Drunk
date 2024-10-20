#include "tableau.hpp"
#include <raylib.h>
#include <cstddef>
#include <cstring>
#include "init.hpp"
#include "util.hpp"

tableau::tableau(init* card_inst) : cards(card_inst) {
  loc_change = true;
  dragging = false;
}
tableau::~tableau() {
  cards = nullptr;
};

void tableau::draw_tableau() {
  for (size_t i = 0; i < COL_NUM; ++i) {
    for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
      if (tableau_seven[i][j].isnt_hidden)
        DrawTexture(tableau_seven[i][j].cards, tableau_seven[i][j].position.x,
                    tableau_seven[i][j].position.y, WHITE);
      else
        DrawTexture(cards->card_back, tableau_seven[i][j].position.x,
                    tableau_seven[i][j].position.y, WHITE);
      tableau_seven[i][j].is_top = false;
      tableau_seven[i].back().is_top = true;
    }
  }
}

void tableau::tableau_init() {
  int j = 0;
  for (size_t i = 24; i < CARDS_NO; ++i) {
    tableau_seven[j].push_back(cards->deck[i]);
    if (i == 24 || i == 26 || i == 29 || i == 33 || i == 38 || i == 44 ||
        i == 51)
      ++j;
  }
}

void tableau::tableau_move(Vector2 mouse_pos) {
  bool ret_w = false;
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    for (size_t i = 0; i < COL_NUM; ++i) {
      for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
        float visi_height = (j == tableau_seven[i].size() - 1)
                                ? static_cast<float>(T_HEIGHT)
                                : 27.0f;
        float card_height = tableau_seven[i][j].cards.height;
        tableau_seven[i][j].cards.height = visi_height;
        ret_w = collision_checker(mouse_pos, offset, old_pos, dragging,
                                  loc_change, tableau_seven[i][j]);
        tableau_seven[i][j].cards.height = card_height;
        i_x = i, i_y = j;
        select_card_sequence(i_x, i_y);
        if (ret_w)
          return;
      }
    }
  } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
    cards_props top_card;
    int y = 0;
    for (size_t i = 0; i < selected_cards.size(); ++i) {
      set_old_pos(old_pos, dragging, loc_change, tableau_seven[i_x][i_y + i],
                  top_card, y);
      y += 27;
      tableau_seven[i_x][i_y + i] = top_card;
    }
  }
  if (dragging && i_x >= 0 && i_x < COL_NUM && i_y >= 0 &&
      i_y < tableau_seven[i_x].size()) {
    cards_props top_card;
    int y = 0;
    for (size_t i = 0; i < selected_cards.size(); ++i) {
      update_pos(offset, tableau_seven[i_x][i_y + i], top_card, y);
      tableau_seven[i_x][i_y + i] = top_card;
      y += 27;
    }
  }
}

void tableau::move_cards_frm_tab(fndtion& n_fnd) {
  if (dragging) {
    Rectangle card_rect = {
        tableau_seven[i_x][i_y].position.x, tableau_seven[i_x][i_y].position.y,
        static_cast<float>(tableau_seven[i_x][i_y].cards.width),
        static_cast<float>(tableau_seven[i_x][i_y].cards.height)};
    Rectangle fnd_rect = set_rect(tableau_seven[i_x][i_y].card_type, n_fnd);
    bool validator = n_fnd.is_valid_move(tableau_seven[i_x][i_y]);
    if (CheckCollisionRecs(card_rect, fnd_rect) && validator) {
      tableau_seven[i_x][i_y].position.x = fnd_rect.x;
      tableau_seven[i_x][i_y].position.y = fnd_rect.y;
      tableau_seven[i_x][i_y].is_captured = true;
      n_fnd.update_fnd(tableau_seven[i_x][i_y]);
      tableau_seven[i_x].pop_back();
      dragging = false;
      if (!tableau_seven[i_x].empty())
        tableau_seven[i_x].back().isnt_hidden = true;

      loc_change = true;
    }
  }
}

bool tableau::check_valid_tab(cards_props frm_tab, cards_props to_tab) {
  if ((to_tab.card_num - frm_tab.card_num == 1) &&
      frm_tab.colour != to_tab.colour)
    return true;
  return false;
}

void tableau::move_cards_frm_tab_tab() {
  if (dragging) {
    Rectangle card_rect = {
        tableau_seven[i_x][i_y].position.x, tableau_seven[i_x][i_y].position.y,
        static_cast<float>(tableau_seven[i_x][i_y].cards.width),
        static_cast<float>(tableau_seven[i_x][i_y].cards.height)};

    for (size_t i = 0; i < COL_NUM; ++i) {
      for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
        Rectangle tab_rect = {
            tableau_seven[i][j].position.x, tableau_seven[i][j].position.y,
            static_cast<float>(tableau_seven[i][j].cards.width),
            static_cast<float>(tableau_seven[i][j].cards.height)};
        if (check_valid_tab(tableau_seven[i_x][i_y], tableau_seven[i][j]) &&
            CheckCollisionRecs(tab_rect, card_rect) &&
            !tableau_seven[i_x][i_y].is_captured &&
            tableau_seven[i][j].isnt_hidden &&
            tableau_seven[i_x][i_y].isnt_hidden && tableau_seven[i][j].is_top) {
          for (size_t k = 0; k < selected_cards.size(); ++k) {
            auto card = deep_copy_card(tableau_seven[i_x][i_y + k]);
            card.position.y = tableau_seven[i][j].position.y;
            card.position.y += 27;
            card.position.x = tableau_seven[i][j].position.x;
            tableau_seven[i].push_back(card);
          }
          for (size_t k = 0; k < selected_cards.size(); ++k) {
            tableau_seven[i_x].pop_back();
            selected_cards.clear();
          }
          dragging = false;
          if (!tableau_seven[i_x].empty())
            tableau_seven[i_x].back().isnt_hidden = true;

          loc_change = true;
          return;
        }
      }
    }
  }
}

bool tableau::card_moved_frm_waste(const cards_props& card_w) {
  Rectangle card_rect = {card_w.position.x, card_w.position.y,
                         static_cast<float>(card_w.cards.width),
                         static_cast<float>(card_w.cards.height)};

  for (size_t i = 0; i < COL_NUM; ++i) {
    for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
      Rectangle tab_rect = {
          tableau_seven[i][j].position.x, tableau_seven[i][j].position.y,
          static_cast<float>(tableau_seven[i][j].cards.width),
          static_cast<float>(tableau_seven[i][j].cards.height)};
      if (check_valid_tab(card_w, tableau_seven[i][j]) &&
          CheckCollisionRecs(tab_rect, card_rect) && !card_w.is_captured &&
          tableau_seven[i][j].isnt_hidden && tableau_seven[i][j].is_top &&
          card_w.isnt_hidden) {
        auto card = deep_copy_card(card_w);
        card.position.y = tableau_seven[i][j].position.y + 27;
        card.position.x = tableau_seven[i][j].position.x;
        tableau_seven[i].push_back(card);
        return true;
      }
    }
  }
  return false;
}

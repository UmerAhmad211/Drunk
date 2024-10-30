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
      if (tableau_seven[i][j].isnt_hidden && !tableau_seven[i].empty())
        DrawTexture(tableau_seven[i][j].cards, tableau_seven[i][j].position.x,
                    tableau_seven[i][j].position.y, WHITE);
      else if (!tableau_seven[i].empty())
        DrawTexture(cards->card_back, tableau_seven[i][j].position.x,
                    tableau_seven[i][j].position.y, WHITE);
      tableau_seven[i][j].is_top = false;
    }
    if (!tableau_seven[i].empty())
      tableau_seven[i].back().is_top = true;
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
  card_flip = LoadSound("assets/card_s.wav");
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
        if (ret_w) {
          i_x = i, i_y = j;
          select_card_sequence(i_x, i_y);
          PlaySound(card_flip);
          return;
        }
      }
    }
  } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
    cards_props top_card;
    int y = 0;
    for (size_t i = 0; i < s_size_cards; ++i) {
      set_old_pos(old_pos, dragging, loc_change, tableau_seven[i_x][i_y + i],
                  top_card, y);
      y += 27;
      tableau_seven[i_x][i_y + i] = top_card;
    }
    PlaySound(card_flip);
  }
  if (dragging && i_x >= 0 && i_x < COL_NUM && i_y >= 0 &&
      i_y < tableau_seven[i_x].size()) {
    cards_props top_card;
    int y = 0;
    for (size_t i = 0; i < s_size_cards; ++i) {
      update_pos(offset, tableau_seven[i_x][i_y + i], top_card, y);
      tableau_seven[i_x][i_y + i] = top_card;
      y += 27;
    }
  }
}

void tableau::move_cards_frm_tab(fndtion& n_fnd, int& points) {
  if (dragging) {
    Rectangle card_rect = {
        tableau_seven[i_x][i_y].position.x, tableau_seven[i_x][i_y].position.y,
        static_cast<float>(tableau_seven[i_x][i_y].cards.width),
        static_cast<float>(tableau_seven[i_x][i_y].cards.height)};
    Rectangle fnd_rect = set_rect(tableau_seven[i_x][i_y].card_type, n_fnd);
    bool validator = n_fnd.is_valid_move(tableau_seven[i_x][i_y]);
    if (CheckCollisionRecs(card_rect, fnd_rect) && validator) {
      move_card(fnd_rect, tableau_seven[i_x][i_y], 0, false);
      tableau_seven[i_x][i_y].is_captured = true;
      n_fnd.update_fnd(tableau_seven[i_x][i_y]);
      tableau_seven[i_x].pop_back();
      dragging = false;
      if (!tableau_seven[i_x].empty())
        tableau_seven[i_x].back().isnt_hidden = true;
      points += 10;
      loc_change = true;
      PlaySound(card_flip);
    }
  }
}

bool tableau::check_valid_tab(cards_props frm_tab, cards_props to_tab) {
  if ((to_tab.card_num - frm_tab.card_num == 1) &&
      frm_tab.colour != to_tab.colour && !frm_tab.is_captured &&
      frm_tab.isnt_hidden && to_tab.isnt_hidden && to_tab.is_top)
    return true;
  return false;
}

void tableau::move_cards_frm_tab_tab(int& points) {
  if (dragging) {
    Rectangle card_rect = {
        tableau_seven[i_x][i_y].position.x, tableau_seven[i_x][i_y].position.y,
        static_cast<float>(tableau_seven[i_x][i_y].cards.width),
        static_cast<float>(tableau_seven[i_x][i_y].cards.height)};
    for (size_t i = 0; i < COL_NUM; ++i) {
      if (tableau_seven[i].size() == 0 &&
          tableau_seven[i_x][i_y].card_num == 13) {
        Rectangle to_tab = {(float)(150 + 160 * i), (float)(258), T_WIDTH,
                            T_HEIGHT};
        if (CheckCollisionRecs(to_tab, card_rect))
          emp_card_up(to_tab, i, false);
        PlaySound(card_flip);
        return;
      }
      for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
        Rectangle tab_rect = {(float)(150 + 160 * i), (float)(258 + 27 * j),
                              T_WIDTH, T_HEIGHT};
        if ((check_valid_tab(tableau_seven[i_x][i_y], tableau_seven[i][j]) ||
             (tableau_seven[i].size() == 0 &&
              tableau_seven[i_x][i_y].card_num == 13)) &&
            CheckCollisionRecs(tab_rect, card_rect)) {
          emp_card_up(tab_rect, i, true);
          loc_change = true;
          points += 5;
          PlaySound(card_flip);
          return;
        }
      }
    }
  }
}

bool tableau::card_moved_frm_waste(cards_props& card_w, int& points) {
  Rectangle card_rect = {card_w.position.x, card_w.position.y,
                         static_cast<float>(card_w.cards.width),
                         static_cast<float>(card_w.cards.height)};

  for (size_t i = 0; i < COL_NUM; ++i) {
    if (tableau_seven[i].size() == 0 && card_w.card_num == 13) {
      s_size_cards = 0;
      ++s_size_cards;
      Rectangle to_tab = {(float)(150 + 160 * i), (float)(258), T_WIDTH,
                          T_HEIGHT};
      if (CheckCollisionRecs(card_rect, to_tab)) {
        move_card(to_tab, card_w, 0, false);
        tableau_seven[i].push_back(card_w);
        PlaySound(card_flip);
        return true;
      }
    }
    for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
      Rectangle tab_rect = {(float)(150 + 160 * i), (float)(258 + 27 * j),
                            T_WIDTH, T_HEIGHT};
      if ((check_valid_tab(card_w, tableau_seven[i][j]) ||
           (tableau_seven[i].size() == 0 && card_w.card_num == 13)) &&
          CheckCollisionRecs(tab_rect, card_rect)) {
        move_card(tab_rect, card_w, 1, false);
        tableau_seven[i].push_back(card_w);
        points += 5;
        PlaySound(card_flip);
        return true;
      }
    }
  }
  return false;
}

void tableau::unload_textures() {
  for (size_t i = 0; i < COL_NUM; ++i) {
    for (size_t j = 0; j < tableau_seven[i].size(); ++j)
      UnloadTexture(tableau_seven[i][j].cards);
  }
  UnloadSound(card_flip);
}

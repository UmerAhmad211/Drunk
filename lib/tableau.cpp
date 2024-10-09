#include "tableau.hpp"
#include <raylib.h>
#include <cstddef>
#include <cstring>
#include "init.hpp"

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
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    for (size_t i = 0; i < COL_NUM; ++i) {
      for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
        Rectangle card_rect = {
            tableau_seven[i][j].position.x, tableau_seven[i][j].position.y,
            static_cast<float>(tableau_seven[i][j].cards.width),
            static_cast<float>(tableau_seven[i][j].cards.height)};

        if (CheckCollisionPointRec(mouse_pos, card_rect) &&
            tableau_seven[i][j].isnt_hidden) {
          dragging = true;
          i_x = i;
          i_y = j;
          offset.x = mouse_pos.x - tableau_seven[i][j].position.x;
          offset.y = mouse_pos.y - tableau_seven[i][j].position.y;

          if (loc_change) {
            old_pos.x = tableau_seven[i][j].position.x;
            old_pos.y = tableau_seven[i][j].position.y;
            loc_change = false;
          }
          return;
        }
      }
    }
  } else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
    tableau_seven[i_x][i_y].position.x = old_pos.x;
    tableau_seven[i_x][i_y].position.y = old_pos.y;
    loc_change = true;
    dragging = false;
  }

  if (dragging) {
    if (i_x >= 0 && i_x < COL_NUM && i_y >= 0 &&
        i_y < tableau_seven[i_x].size()) {
      Vector2 nmouse_pos = GetMousePosition();
      tableau_seven[i_x][i_y].position.x = nmouse_pos.x - offset.x;
      tableau_seven[i_x][i_y].position.y = nmouse_pos.y - offset.y;
    }
  }
}

void tableau::move_cards_frm_tab(fndtion& n_fnd) {
  Vector2 nmouse_pos = GetMousePosition();
  if (dragging) {
    Rectangle card_rect = {
        tableau_seven[i_x][i_y].position.x, tableau_seven[i_x][i_y].position.y,
        static_cast<float>(tableau_seven[i_x][i_y].cards.width),
        static_cast<float>(tableau_seven[i_x][i_y].cards.height)};
    Rectangle fnd_rect = set_rect(tableau_seven[i_x][i_y].card_type, n_fnd);
    Rectangle intersect_rect = GetCollisionRec(card_rect, fnd_rect);
    Rectangle cursor_box = {nmouse_pos.x - 3, nmouse_pos.y - 3, 3, 3};
    float intersect_area = intersect_rect.width * intersect_rect.height;
    float cursor_area = cursor_box.width * cursor_box.height;
    bool validator = n_fnd.is_valid_move(tableau_seven[i_x][i_y]);
    if (intersect_area / cursor_area >= CAPT_THRES && validator) {
      tableau_seven[i_x][i_y].position.x =
          fnd_rect.x +
          (fnd_rect.width - tableau_seven[i_x][i_y].cards.width) / 2;
      tableau_seven[i_x][i_y].position.y =
          fnd_rect.y +
          (fnd_rect.height - tableau_seven[i_x][i_y].cards.height) / 2;
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
            tableau_seven[i_x][i_y].isnt_hidden) {
          auto card = tableau_seven[i_x].back();
          tableau_seven[i_x].pop_back();
          card.position.y = tableau_seven[i][j].position.y;
          card.position.y += 27;
          card.position.x = tableau_seven[i][j].position.x;
          tableau_seven[i].push_back(card);
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

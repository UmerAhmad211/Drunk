#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <vector>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"

#define COL_NUM 7

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[COL_NUM];
  std::vector<cards_props> selected_cards;
  bool loc_change;
  bool dragging;
  size_t i_x = 0, i_y = 0;
  Vector2 offset = {0, 0}, old_pos = {0, 0};
  void select_card_sequence(size_t col, size_t start_x) {
    selected_cards.clear();
    for (size_t i = start_x; i < tableau_seven[col].size(); ++i)
      if (tableau_seven[col][i].isnt_hidden)
        selected_cards.push_back(tableau_seven[col][i]);
  }

 public:
  tableau(init*);
  ~tableau();
  void draw_tableau();
  void tableau_init();
  void update_tableau();
  void tableau_move(Vector2);
  void move_cards_frm_tab(fndtion&);
  void move_cards_frm_tab_tab();
  bool check_valid_tab(cards_props, cards_props);
  bool card_moved_frm_waste(const cards_props&);
};

#endif
#define TABLEAU_HPP

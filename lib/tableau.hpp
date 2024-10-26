#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <raylib.h>
#include <vector>
#include "util.hpp"

#define COL_NUM 7

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[COL_NUM];
  bool loc_change;
  bool dragging;
  size_t i_x = 0;
  size_t i_y = 0;
  size_t s_size_cards = 0;
  Vector2 offset = {0, 0}, old_pos = {0, 0};
  void select_card_sequence(size_t col, size_t start_x) {
    s_size_cards = 0;
    for (size_t i = start_x; i < tableau_seven[col].size(); ++i)
      ++s_size_cards;
  }

 public:
  tableau(init*);
  ~tableau();
  void unload_textures();
  void draw_tableau();
  void tableau_init();
  void update_tableau();
  void tableau_move(Vector2);
  void move_cards_frm_tab(fndtion&);
  void move_cards_frm_tab_tab();
  bool check_valid_tab(cards_props, cards_props);
  bool card_moved_frm_waste(cards_props&);
};

#endif

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
  Rectangle set_rect(std::string card_type, fndtion n_fnd) {
    if (card_type == "assets/heart")
      return n_fnd.fnd_rec1;
    else if (card_type == "assets/diams")
      return n_fnd.fnd_rec2;
    else if (card_type == "assets/clubs")
      return n_fnd.fnd_rec3;
    else
      return n_fnd.fnd_rec4;
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
};

#endif
#define TABLEAU_HPP

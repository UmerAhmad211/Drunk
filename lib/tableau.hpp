#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <vector>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"

#define COL_NUM 7
#define CAPT_THRES 0.5f

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[COL_NUM];
  bool is_first;
  bool dragging = false;
  size_t i_x = 0, i_y = 0;
  Vector2 offset = {0, 0};
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
  void is_valid_move(fndtion&);
};

#endif
#define TABLEAU_HPP

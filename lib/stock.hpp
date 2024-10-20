#ifndef STOCK_HPP
#define STOCK_HPP
#include <stack>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"
#include "tableau.hpp"

class stock {
  init* init_cards;
  unsigned int spacing;
  std::stack<cards_props> cards_stock;
  std::stack<cards_props> waste;
  bool loc_change;
  bool dragging;
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
  stock(init*);
  ~stock();
  void draw_stock();
  void move_to_waste();
  void restock();
  void stock_clicked(Vector2);
  void waste_moved(Vector2);
  void move_cards_frm_sw(fndtion&);
  void move_cards_frm_wt(tableau&);
};

#endif

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
  Sound click_s;
  bool loc_change;
  bool dragging;
  Vector2 offset = {0, 0}, old_pos = {0, 0};

 public:
  stock(init*);
  ~stock();
  void draw_stock();
  void move_to_waste(int& points);
  void restock();
  void stock_clicked(Vector2, int&);
  void waste_moved(Vector2);
  void move_cards_frm_sw(fndtion&, int&);
  void move_cards_frm_wt(tableau&, int&);
  void unload_textures();
};

#endif

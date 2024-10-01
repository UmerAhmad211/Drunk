#ifndef STOCK_HPP
#define STOCK_HPP
#include <stack>
#include "init.hpp"
#include "raylib.h"

class stock {
  init* init_cards;
  unsigned int spacing;
  std::stack<cards_props> cards_stock;
  std::stack<cards_props> waste;

 public:
  stock(init*);
  ~stock();
  void draw_stock();
  void move_to_waste();
  void restock();
  void stock_clicked(Vector2);
};

#endif

#ifndef STOCK_HPP
#define STOCK_HPP
#include "init.hpp"

class stock {
  init* cards;

 public:
  stock(init*);
  ~stock();
  void draw_stock();
};

#endif

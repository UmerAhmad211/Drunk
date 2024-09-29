#ifndef TABLEAU_HPP
#define TABLEAU_HPP
#include "init.hpp"

class tableau {
  init* cards;

 public:
  tableau(init*);
  ~tableau();
  void draw_tableau();
};

#endif  // !TABLEAU_HPP
#define TABLEAU_HPP

#ifndef TABLEAU_HPP
#define TABLEAU_HPP
#include <vector>
#include "init.hpp"

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[7];

 public:
  tableau(init*);
  ~tableau();
  void draw_tableau();
  void tableau_init();
  void update_tableau();
  void tableau_move();
};

#endif
#define TABLEAU_HPP

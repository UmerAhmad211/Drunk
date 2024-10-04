#ifndef TABLEAU_HPP
#define TABLEAU_HPP
#include <raylib.h>
#include <vector>
#include "init.hpp"

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[7];
  bool is_first;
  // bool drag = false, captured = false;
  // int x = 630, y = 29, spacing = 160, width = 127, height = 172;
  // Rectangle fnd_recs[4] = {{x, y, width, height},
  //                          {x + spacing, y, width, height},
  //                          {x + (spacing * 2), y, width, height},
  //                          {x + (spacing * 3), y, width, height}};

 public:
  tableau(init*);
  ~tableau();
  void draw_tableau();
  void tableau_init();
  void update_tableau();
  void tableau_move(Vector2);
};

#endif
#define TABLEAU_HPP

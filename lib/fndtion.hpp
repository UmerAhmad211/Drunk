#ifndef FNDTION_HPP
#define FNDTION_HPP
#include <vector>
#include "init.hpp"

#define FND_NO 4
#define FND_X 630
#define FND_Y 29

class fndtion {
  init* fnd_track;
  std::vector<cards_props> fnd_four[FND_NO]{};
  int spacing;

 public:
  fndtion(init*);
  ~fndtion();
  void draw_fnd();
  void update_fnd();
};

#endif

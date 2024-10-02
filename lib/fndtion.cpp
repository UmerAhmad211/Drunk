#include "fndtion.hpp"
#include <raylib.h>
#include <cstddef>

fndtion::fndtion(init* cards_inst) : fnd_track(cards_inst) {
  spacing = 0;
}
fndtion::~fndtion() {
  delete fnd_track;
}

void fndtion::draw_fnd() {
  for (size_t i = 0; i < FND_NO; ++i) {
    for (size_t j = 0; j < fnd_four[i].size(); ++j)
      DrawTexture(fnd_four[i][j].cards, FND_X + spacing, FND_Y, WHITE);

    spacing += 150;
    spacing %= 600;
  }
}

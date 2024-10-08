#include "fndtion.hpp"
#include <raylib.h>
#include <cstddef>

fndtion::fndtion() {};
fndtion::~fndtion() {
  for (size_t i = 0; i < FND_NO; ++i) {
    for (size_t j = 0; j < fnd_four[i].size(); ++j)
      UnloadTexture(fnd_four[i][j].cards);
  }
}

void fndtion::draw_fnd() {
  for (size_t i = 0; i < FND_NO; ++i) {
    for (size_t j = 0; j < fnd_four[i].size(); ++j) {
      if (fnd_four[i][j].isnt_hidden)
        DrawTexture(fnd_four[i][j].cards, fnd_four[i][j].position.x,
                    fnd_four[i][j].position.y, WHITE);
    }
  }
}

void fndtion::update_fnd(cards_props cards) {
  if (cards.card_type == "assets/heart")
    fnd_four[0].push_back(cards);
  else if (cards.card_type == "assets/diams")
    fnd_four[1].push_back(cards);
  else if (cards.card_type == "assets/clubs")
    fnd_four[2].push_back(cards);
  else
    fnd_four[3].push_back(cards);
}

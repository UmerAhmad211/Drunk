#include "tableau.hpp"
#include <raylib.h>
#include <cstddef>
#include <cstring>
#include "init.hpp"

tableau::tableau(init* card_inst) : cards(card_inst) {}
tableau::~tableau(){};

void tableau::draw_tableau() {
  int x = 150, spacing = 160, tempx = 150;
  int y = 258, j = 0, card_col = 7;
  for (size_t i = 24; i < CARDS_NO; ++i) {
    if (cards->deck[i].isnt_hidden)
      DrawTexture(cards->deck[i].cards, x, y, WHITE);
    else
      DrawTexture(cards->card_back, x, y, WHITE);
    x += spacing;
    j++;
    if (j == card_col) {
      x = tempx + spacing;
      tempx += spacing;
      y += 27;
      j = 0;
      --card_col;
    }
  }
}

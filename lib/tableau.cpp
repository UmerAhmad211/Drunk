#include "tableau.hpp"
#include <raylib.h>
#include <cstddef>
#include <cstring>
#include "init.hpp"

tableau::tableau(init* card_inst) : cards(card_inst) {}
tableau::~tableau() {
  delete cards;
};

void tableau::draw_tableau() {
  int x = 150, spacing = 160;
  int y = 258;
  for (size_t i = 0; i < 7; ++i) {
    for (size_t j = 0; j < tableau_seven[i].size(); ++j) {
      if (tableau_seven[i][j].isnt_hidden)
        DrawTexture(tableau_seven[i][j].cards, x, y, WHITE);
      else
        DrawTexture(cards->card_back, x, y, WHITE);
      y += 27;
    }
    x += spacing;
    y = 258;
  }
}

void tableau::tableau_init() {
  int card_col = 7, j = 0;
  for (size_t i = 24; i < CARDS_NO; ++i) {
    tableau_seven[j].push_back(cards->deck[i]);
    if (i == 24 || i == 26 || i == 29 || i == 33 || i == 38 || i == 44 ||
        i == 51)
      ++j;
  }
}

// void tableau::tableau_move(){
//
// }

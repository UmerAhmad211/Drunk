#include "fndtion.hpp"
#include <raylib.h>
#include <cstddef>

fndtion::fndtion() {};
fndtion::~fndtion() {}

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
  else if (cards.card_type == "assets/spade")
    fnd_four[3].push_back(cards);
}

bool fndtion::is_valid_move(cards_props card) {
  int suit_i;
  switch (card.card_type[7]) {
    case 'h':
      suit_i = 0;
      break;
    case 'd':
      suit_i = 1;
      break;
    case 'c':
      suit_i = 2;
      break;
    case 's':
      suit_i = 3;
      break;
    default:
      return false;
  }

  if (fnd_four[suit_i].empty()) {
    return card.card_num == 1;
  }
  return card.card_num - fnd_four[suit_i].back().card_num == 1;
}

bool fndtion::is_win() {
  if (fnd_four[0].back().card_num == 13 && fnd_four[1].back().card_num == 13 &&
      fnd_four[2].back().card_num == 13 && fnd_four[3].back().card_num == 13)
    return true;
  return false;
}

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
  if (card.card_type == "assets/heart") {
    if (!fnd_four[0].empty()) {
      if (card.card_num - fnd_four[0].back().card_num == 1)
        return true;
      return false;
    } else if (card.card_num == 1)
      return true;
    return false;
  } else if (card.card_type == "assets/diams") {
    if (!fnd_four[1].empty()) {
      if (card.card_num - fnd_four[1].back().card_num == 1)
        return true;
      return false;
    } else if (card.card_num == 1)
      return true;
    return false;
  } else if (card.card_type == "assets/clubs") {
    if (!fnd_four[2].empty()) {
      if (card.card_num - fnd_four[2].back().card_num == 1)
        return true;
      return false;
    } else if (card.card_num == 1)
      return true;
    return false;
  } else if (card.card_type == "assets/spade") {
    if (!fnd_four[3].empty()) {
      if (card.card_num - fnd_four[3].back().card_num == 1)
        return true;
      return false;
    } else if (card.card_num == 1)
      return true;
    return false;
  }
  return false;
}

#include "../include/fndtion.hpp"
#include <raylib.h>
#include <cstddef>

Fndtion::Fndtion() = default;
Fndtion::~Fndtion() = default;

void Fndtion::draw_fnd() {
  for (size_t i = 0; i < FND_NO; ++i) {
    if (!fnd_four[i].empty()) {
      DrawTexture(fnd_four[i].back().cards, fnd_four[i].back().position.x,
                  fnd_four[i].back().position.y, WHITE);
    }
  }
}

void Fndtion::update_fnd(const Cards_Props& cards) {
  switch (cards.card_type[7]) {
    case 'h':
      fnd_four[0].push_back(cards);
      return;
    case 'd':
      fnd_four[1].push_back(cards);
      return;
    case 'c':
      fnd_four[2].push_back(cards);
      return;
    default:
      fnd_four[3].push_back(cards);
      return;
  }
}

bool Fndtion::is_valid_move(const Cards_Props& card) {
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
    default:
      suit_i = 3;
      break;
  }

  if (fnd_four[suit_i].empty()) {
    return card.card_num == 1;
  }
  return card.card_num - fnd_four[suit_i].back().card_num == 1;
}

bool Fndtion::is_win() const {
  for (int i = 0; i < 4; ++i) {
    if (fnd_four[i].empty() || fnd_four[i].back().card_num != 13)
      return false;
  }
  return true;
}

void Fndtion::unload_textures() const {
  for (size_t i = 0; i < FND_NO; ++i) {
    for (size_t j = 0; j < fnd_four[i].size(); ++j)
      UnloadTexture(fnd_four[i][j].cards);
  }
}

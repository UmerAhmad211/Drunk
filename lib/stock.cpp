#include "stock.hpp"
#include <raylib.h>

stock::stock(init* cards_inst) : cards(cards_inst) {}
stock::~stock() {}

void stock::draw_stock() {
  const int cord_x = 64;
  const int cord_y = 29;
  DrawTexture(cards->card_back, cord_x, cord_y, WHITE);
}

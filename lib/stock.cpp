#include "stock.hpp"
#include <raylib.h>
#include <iostream>

#define CORD_X 64
#define CORD_Y 29
#define S_SIZE 23

stock::stock(init* cards_inst) : init_cards(cards_inst) {
  for (size_t i = 0; i <= S_SIZE; ++i)
    cards_stock.push(init_cards->deck[i]);
  if (cards_stock.empty())
    std::cerr << "Empty." << std::endl;
  spacing = 150;
}
stock::~stock() {
  delete init_cards;
}

void stock::draw_stock() {
  DrawTexture(init_cards->card_back, CORD_X, CORD_Y, WHITE);
  if (!waste.empty())
    DrawTexture(waste.top().cards, CORD_X + spacing, CORD_Y, WHITE);
}

void stock::stock_clicked(Vector2 mouse_pos) {
  if ((CheckCollisionPointRec(mouse_pos,
                              (Rectangle){CORD_X, CORD_Y, T_WIDTH, T_HEIGHT})))
    move_to_waste();
}

void stock::move_to_waste() {
  if (!cards_stock.empty()) {
    cards_stock.top().isnt_hidden = true;
    waste.push(cards_stock.top());
    cards_stock.pop();
  } else
    restock();
}

void stock::restock() {
  for (; !waste.empty();) {
    waste.top().isnt_hidden = false;
    cards_stock.push(waste.top());
    waste.pop();
  }
  draw_stock();
}

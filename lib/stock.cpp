#include "stock.hpp"
#include <raylib.h>
#include <iostream>
#include "util.hpp"

#define CORD_X 64
#define CORD_Y 29
#define S_SIZE 23

stock::stock(init* cards_inst) : init_cards(cards_inst) {
  for (size_t i = 0; i <= S_SIZE; ++i)
    cards_stock.push(init_cards->deck[i]);

  spacing = 150;
  loc_change = true;
  dragging = false;
}
stock::~stock() {
  init_cards = nullptr;
}

void stock::draw_stock() {
  DrawTexture(init_cards->card_back, CORD_X, CORD_Y, WHITE);
  if (!waste.empty())
    DrawTexture(waste.top().cards, waste.top().position.x,
                waste.top().position.y, WHITE);
}

void stock::stock_clicked(Vector2 mouse_pos) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    if ((CheckCollisionPointRec(
            mouse_pos, (Rectangle){CORD_X, CORD_Y, T_WIDTH, T_HEIGHT})))
      move_to_waste();
  }
}
void stock::move_to_waste() {
  if (!cards_stock.empty()) {
    auto top_card = deep_copy_card(cards_stock.top());
    cards_stock.pop();
    top_card.isnt_hidden = true;
    top_card.position.x = CORD_X + spacing;
    top_card.position.y = CORD_Y;
    waste.push(top_card);
  } else
    restock();
}

void stock::restock() {
  for (; !waste.empty();) {
    auto top_card = deep_copy_card(waste.top());
    waste.pop();
    top_card.isnt_hidden = false;
    cards_stock.push(top_card);
  }
  draw_stock();
}

void stock::waste_moved(Vector2 mouse_pos) {
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !waste.empty())
    collision_checker(mouse_pos, offset, old_pos, dragging, loc_change,
                      waste.top());
  else if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging &&
           !waste.empty() && !waste.top().is_captured) {
    cards_props top_card;
    set_old_pos(old_pos, dragging, loc_change, waste.top(), top_card, 0);
    waste.pop();
    waste.push(top_card);
  }
  if (dragging && !waste.empty() && !waste.top().is_captured) {
    cards_props top_card;
    update_pos(offset, waste.top(), top_card, 0);
    waste.pop();
    waste.push(top_card);
  }
}

void stock::move_cards_frm_sw(fndtion& n_fnd) {
  if (dragging) {
    Rectangle card_rect = {waste.top().position.x, waste.top().position.y,
                           static_cast<float>(waste.top().cards.width),
                           static_cast<float>(waste.top().cards.height)};
    Rectangle fnd_rect = set_rect(waste.top().card_type, n_fnd);
    bool validator = n_fnd.is_valid_move(waste.top());
    if (CheckCollisionRecs(card_rect, fnd_rect) && validator) {
      auto top_card = deep_copy_card(waste.top());
      waste.pop();
      top_card.position.x = fnd_rect.x;
      top_card.position.y = fnd_rect.y;
      top_card.is_captured = true;
      n_fnd.update_fnd(top_card);
      dragging = false;
      loc_change = true;
    }
  }
}

void stock::move_cards_frm_wt(tableau& n_tab) {
  if (dragging) {
    bool yay = n_tab.card_moved_frm_waste(waste.top());
    if (yay) {
      waste.pop();
      dragging = false;
      loc_change = true;
    }
  }
}

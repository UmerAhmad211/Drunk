#include "util.hpp"

cards_props deep_copy_card(const cards_props& orig) {
  cards_props copy = orig;
  Image img = LoadImageFromTexture(orig.cards);
  copy.cards = LoadTextureFromImage(img);
  UnloadImage(img);
  return copy;
}

Rectangle set_rect(const std::string& card_type, const fndtion& n_fnd) {
  switch (card_type[7]) {
    case 'h':
      return n_fnd.fnd_rec1;
    case 'd':
      return n_fnd.fnd_rec2;
    case 'c':
      return n_fnd.fnd_rec3;
    default:
      return n_fnd.fnd_rec4;
  }
}

bool collision_checker(const Vector2& mouse_pos,
                       Vector2& offset,
                       Vector2& old_pos,
                       bool& dragging,
                       bool& loc_change,
                       const cards_props& card) {
  Rectangle card_rect = {card.position.x, card.position.y,
                         static_cast<float>(card.cards.width),
                         static_cast<float>(card.cards.height)};
  if (CheckCollisionPointRec(mouse_pos, card_rect) && card.isnt_hidden) {
    dragging = true;
    offset.x = mouse_pos.x - card.position.x;
    offset.y = mouse_pos.y - card.position.y;
    if (loc_change) {
      old_pos.x = card.position.x;
      old_pos.y = card.position.y;
      loc_change = false;
    }
    return true;
  }
  return false;
}

void set_old_pos(Vector2& old_pos,
                 bool& dragging,
                 bool& loc_change,
                 const cards_props& card,
                 cards_props& top_card,
                 int y) {
  top_card = deep_copy_card(card);
  top_card.position.x = old_pos.x;
  top_card.position.y = old_pos.y + y;
  loc_change = true;
  dragging = false;
}

void update_pos(const Vector2& offset,
                const cards_props& card,
                cards_props& top_card,
                int y) {
  Vector2 nmouse_pos = GetMousePosition();
  top_card = deep_copy_card(card);
  top_card.position.x = nmouse_pos.x - offset.x;
  top_card.position.y = nmouse_pos.y - offset.y + y;
}

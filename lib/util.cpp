#include "util.hpp"

cards_props deep_copy_card(const cards_props& orig) {
  cards_props copy = orig;
  Image img = LoadImageFromTexture(orig.cards);
  copy.cards = LoadTextureFromImage(img);
  UnloadImage(img);
  return copy;
}

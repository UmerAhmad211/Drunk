#ifndef LIB_HPP
#define LIB_HPP
#include "raylib.h"

#define CARDS_NO 52
#define T_WIDTH 127
#define T_HEIGHT 172

struct cards_props {
  Texture2D cards;
  bool isnt_hidden;
};
class init {
 public:
  init();
  ~init();
  Texture2D card_back;
  cards_props deck[CARDS_NO]{};
  void load_textures();
  void unload_textures();
  void shuffle_cards();
  void init_cards_state();
};

#endif

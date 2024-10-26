#include "init.hpp"
#include <raylib.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <string>
#include <utility>

init::init() {
  card_back = LoadTexture("assets/card_back.png");
}
init::~init() {}

void init::load_textures() {
  const std::vector<std::string> card_base = {"assets/heart", "assets/diams",
                                              "assets/clubs", "assets/spade"};
  const std::vector<std::string> card_values = {"01", "02", "03", "04", "05",
                                                "06", "07", "08", "09", "10",
                                                "11", "12", "13"};
  const char card_clr[2] = {'r', 'b'};
  for (size_t i = 0; i < CARDS_NO; ++i) {
    size_t suit = i / 13;
    size_t value = i % 13;
    std::string filename = card_base[suit] + card_values[value] + ".png";
    Image img = LoadImage(filename.c_str());
    ImageResize(&img, T_WIDTH, T_HEIGHT);
    deck[i].cards = LoadTextureFromImage(img);
    deck[i].card_type = card_base[suit];
    deck[i].card_num = value + 1;
    deck[i].is_captured = false;
    deck[i].colour = card_clr[i > 25];
    deck[i].is_top = false;
    UnloadImage(img);
  }
}

void init::shuffle_cards() {
  srand(time(0));
  for (size_t i = 0; i < CARDS_NO; ++i) {
    int rand1 = rand() % 52;
    int rand2 = rand() % 52;
    if (rand1 == rand2)
      continue;
    std::swap(deck[rand1], deck[rand2]);
  }
}

void init::init_cards_state() {
  int x = 150, spacing = 160, y = 258;

  for (size_t i = 24; i < CARDS_NO; ++i) {
    bool is_first_in_column = (i == 24 || i == 26 || i == 29 || i == 33 ||
                               i == 38 || i == 44 || i == 51);

    deck[i].isnt_hidden = is_first_in_column;
    deck[i].is_top = is_first_in_column;

    deck[i].position.x = x;
    deck[i].position.y = y;

    y = is_first_in_column ? 258 : y + 27;
    x += is_first_in_column * spacing;
  }
}

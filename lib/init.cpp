#include "init.hpp"
#include <raylib.h>
#include <cstddef>
#include <random>
#include <string>
#include <utility>

init::init() {
  card_back = LoadTexture("assets/card_back.png");
}
init::~init() {}
// clean code
void init::load_textures() {
  const int T_WIDTH = 127;
  const int T_HEIGHT = 172;
  std::string card_base[] = {"assets/clubs", "assets/spades", "assets/hearts",
                             "assets/diam"};
  const char* card_values[] = {"1", "2", "3",  "4",  "5",  "6", "7",
                               "8", "9", "10", "11", "12", "13"};

  for (size_t i = 0; i < CARDS_NO; ++i) {
    size_t suit = i / 13;
    size_t value = i % 13;
    std::string filename = card_base[suit] + card_values[value] + ".png";
    Image img = LoadImage(filename.c_str());
    ImageResize(&img, T_WIDTH, T_HEIGHT);
    deck[i].cards = LoadTextureFromImage(img);
  }
  card_back = LoadTexture("assets/card_back.png");
}

void init::shuffle_cards() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> num(0, 51);
  for (size_t i = 0; i < CARDS_NO; ++i) {
    int rand1 = num(gen);
    int rand2 = num(gen);
    if (rand1 == rand2)
      continue;
    std::swap(deck[rand1].cards, deck[rand2].cards);
  }
}

void init::init_cards_state() {
  for (size_t i = 24; i < CARDS_NO; ++i) {
    if (i == 24 || i == 31 || i == 37 || i == 42 || i == 46 || i == 49 ||
        i == 51)
      deck[i].isnt_hidden = true;
  }
}

void init::unload_textures() {
  for (size_t i = 0; i < CARDS_NO; ++i)
    UnloadTexture(deck[i].cards);
  UnloadTexture(card_back);
}

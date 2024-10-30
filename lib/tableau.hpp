#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <raylib.h>
#include <cstddef>
#include <vector>
#include "init.hpp"
#include "util.hpp"

#define COL_NUM 7

class tableau {
  init* cards;
  std::vector<cards_props> tableau_seven[COL_NUM];
  bool loc_change;
  bool dragging;
  size_t i_x = 0;
  size_t i_y = 0;
  size_t s_size_cards = 0;
  Vector2 offset = {0, 0}, old_pos = {0, 0};
  Sound card_flip;
  void select_card_sequence(size_t col, size_t start_x) {
    s_size_cards = 0;
    s_size_cards = tableau_seven[col].size() - start_x;
  }

  void move_card(const Rectangle& to_tab,
                 cards_props& card,
                 size_t k,
                 const bool& add_y) {
    card.position.x = to_tab.x;
    card.position.y = to_tab.y + (27 * (k + add_y));
  }

  void emp_card_up(const Rectangle& to_tab,
                   const size_t& i,
                   const bool& add_y) {
    for (size_t k = 0; k < s_size_cards; ++k) {
      move_card(to_tab, tableau_seven[i_x][i_y + k], k, add_y);
      tableau_seven[i].push_back(tableau_seven[i_x][i_y + k]);
    }
    for (size_t i = 0; i < s_size_cards; ++i)
      tableau_seven[i_x].pop_back();
    if (!tableau_seven[i_x].empty())
      tableau_seven[i_x].back().isnt_hidden = true;
  }

 public:
  tableau(init*);
  ~tableau();
  void unload_textures();
  void draw_tableau();
  void tableau_init();
  void update_tableau();
  void tableau_move(Vector2);
  void move_cards_frm_tab(fndtion&, int&);
  void move_cards_frm_tab_tab(int&);
  bool check_valid_tab(cards_props, cards_props);
  bool card_moved_frm_waste(cards_props&, int&);
};

#endif

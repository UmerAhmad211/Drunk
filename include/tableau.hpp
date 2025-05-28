#ifndef TABLEAU_HPP
#define TABLEAU_HPP

#include <raylib.h>
#include <cstddef>
#include <vector>
#include "init.hpp"
#include "util.hpp"

#define COL_NUM 7

class Tableau {
	Init *cards;
	std::vector<Cards_Props> tableau_seven[COL_NUM];
	bool loc_change;
	bool dragging;
	size_t i_x = 0;
	size_t i_y = 0;
	size_t s_size_cards = 0;
	Vector2 offset = { 0, 0 }, old_pos = { 0, 0 };
	Sound card_flip;
	void select_card_sequence(const size_t &, const size_t &);
	void move_card(const Rectangle &, Cards_Props &, const size_t &,
		       const bool &);
	void emp_card_up(const Rectangle &, const size_t &, const bool &);

    public:
	Tableau(Init *);
	~Tableau();
	void unload_textures();
	void draw_tableau();
	void tableau_init();
	void update_tableau();
	void tableau_move(Vector2);
	void move_cards_from_tab(Fndtion &, int &);
	void move_cards_from_tab_to_tab(int &);
	bool check_valid_tab(Cards_Props, Cards_Props);
	bool card_moved_from_waste(Cards_Props &, int &);
};

#endif

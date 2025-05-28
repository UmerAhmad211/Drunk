#ifndef STOCK_HPP
#define STOCK_HPP
#include <stack>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"
#include "tableau.hpp"

class Stock {
	Init *init_cards;
	unsigned int spacing;
	std::stack<Cards_Props> cards_stock;
	std::stack<Cards_Props> waste;
	Sound click_s;
	bool loc_change;
	bool dragging;
	Vector2 offset = { 0, 0 }, old_pos = { 0, 0 };

    public:
	Stock(Init *);
	~Stock();
	void draw_stock();
	void move_to_waste(int &points);
	void restock();
	void stock_clicked(Vector2, int &);
	void waste_moved(Vector2);
	void move_cards_from_stock_to_waste(Fndtion &, int &);
	void move_cards_from_waste_to_tableau(Tableau &, int &);
	void unload_textures();
};

#endif

#ifndef INIT_HPP
#define INIT_HPP

#include <iostream>
#include <vector>
#include "raylib.h"

#define CARDS_NO 52
#define T_WIDTH 127
#define T_HEIGHT 172

struct Cards_Props {
	Texture2D cards;
	Vector2 position;
	std::string card_type;
	int card_num;
	bool is_captured;
	bool is_top;
	bool isnt_hidden;
	char colour;
};

class Init {
    public:
	Init();
	~Init();
	Texture2D card_back;
	Cards_Props deck[CARDS_NO]{};
	void load_textures();
	void shuffle_cards();
	void init_cards_state();
};

#endif

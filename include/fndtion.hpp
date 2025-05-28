#ifndef FNDTION_HPP
#define FNDTION_HPP

#include <raylib.h>
#include <vector>
#include "init.hpp"

#define FND_NO 4
#define FND_X 630
#define FND_Y 29
#define CAPT_THRES 0.5f

class Fndtion {
	std::vector<Cards_Props> fnd_four[FND_NO];

    public:
	const Rectangle fnd_rec1 = { FND_X, FND_Y, T_WIDTH, T_HEIGHT };
	const Rectangle fnd_rec2 = { FND_X + 160, FND_Y, T_WIDTH, T_HEIGHT };
	const Rectangle fnd_rec3 = { FND_X + (2 * 160), FND_Y, T_WIDTH,
				     T_HEIGHT };
	const Rectangle fnd_rec4 = { FND_X + (3 * 160), FND_Y, T_WIDTH,
				     T_HEIGHT };
	Fndtion();
	~Fndtion();
	void draw_fnd();
	void update_fnd(const Cards_Props &);
	bool is_valid_move(const Cards_Props &);
	bool is_win() const;
	void unload_textures() const;
};

#endif

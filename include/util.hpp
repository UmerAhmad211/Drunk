#ifndef UTIL_HPP
#define UTIL_HPP

#include <stack>
#include <vector>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"

Cards_Props
deep_copy_card(const Cards_Props &);

Rectangle
set_rect(const std::string &, const Fndtion &);

bool
collision_checker(const Vector2 &, Vector2 &, Vector2 &, bool &, bool &,
		  const Cards_Props &);

void
set_old_pos(Vector2 &, bool &, bool &, const Cards_Props &,
	    Cards_Props &top_card, int y);

void
update_pos(const Vector2 &offset, const Cards_Props &card,
	   Cards_Props &top_card, int y);

#endif // !UTIL_HPP

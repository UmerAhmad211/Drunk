#ifndef UTIL_HPP
#define UTIL_HPP

#include <stack>
#include <vector>
#include "fndtion.hpp"
#include "init.hpp"
#include "raylib.h"

cards_props deep_copy_card(const cards_props&);
Rectangle set_rect(const std::string&, const fndtion&);

bool collision_checker(const Vector2&,
                       Vector2&,
                       Vector2&,
                       bool&,
                       bool&,
                       const cards_props&);

void set_old_pos(Vector2&,
                 bool&,
                 bool&,
                 const cards_props&,
                 cards_props& top_card,
                 int y);

void update_pos(const Vector2& offset,
                const cards_props& card,
                cards_props& top_card,
                int y);

#endif  // !UTIL_HPP

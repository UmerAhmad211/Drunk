#include <sys/types.h>
#include <iostream>
#include "../lib/init.hpp"
#include "../lib/stock.hpp"
#include "../lib/tableau.hpp"
#include "raylib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solitaire");

  init card_l;

  card_l.load_textures();

  card_l.shuffle_cards();
  card_l.init_cards_state();
  stock n_stock(&card_l);
  tableau n_tab(&card_l);

  Texture2D texture = LoadTexture("assets/coz1.png");
  Texture2D green_back = LoadTexture("assets/boardsol.png");
  bool on_title = true;
  SetTargetFPS(60);

  std::cout << "Current working directory: " << GetWorkingDirectory()
            << std::endl;

  while (!WindowShouldClose()) {
    if (on_title) {
      if (IsKeyPressed(KEY_ENTER))
        on_title = false;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (on_title) {
      DrawTexture(texture, SCREEN_WIDTH / 2 - texture.width / 2,
                  SCREEN_HEIGHT / 2 - texture.height / 2, WHITE);
      DrawText("Solitaire", 100, 300, 100, WHITE);
      DrawText("Press enter to continue.", 540, 640, 20, WHITE);
    } else {
      DrawTexture(green_back, SCREEN_WIDTH / 2 - green_back.width / 2,
                  SCREEN_HEIGHT / 2 - texture.height / 2, WHITE);
      n_tab.draw_tableau();
      n_stock.draw_stock();
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      Vector2 mouse_pos = GetMousePosition();
      n_stock.stock_clicked(mouse_pos);
      std::cout << "Mouse pos: " << "X: " << mouse_pos.x << "Y: " << mouse_pos.y
                << std::endl;
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  UnloadTexture(green_back);
  card_l.unload_textures();

  CloseWindow();

  return 0;
}

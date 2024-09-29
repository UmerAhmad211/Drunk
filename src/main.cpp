#include <iostream>
#include "../lib/init.hpp"
#include "../lib/tableau.hpp"
#include "raylib.h"

int main() {
  const int screenWidth = 1280;
  const int screenHeight = 720;

  InitWindow(screenWidth, screenHeight, "Solitaire");

  init card_l;

  card_l.load_textures();

  card_l.shuffle_cards();
  card_l.init_cards_state();

  tableau n_tab(&card_l);

  Texture2D texture = LoadTexture("assets/coz1.png");
  Texture2D green_back = LoadTexture("assets/board.png");
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
      DrawTexture(texture, screenWidth / 2 - texture.width / 2,
                  screenHeight / 2 - texture.height / 2, WHITE);
      DrawText("Solitaire", 100, 300, 100, WHITE);
      DrawText("Press enter to continue.", 540, 640, 20, WHITE);
    } else {
      DrawTexture(green_back, screenWidth / 2 - green_back.width / 2,
                  screenHeight / 2 - texture.height / 2, WHITE);
      n_tab.draw_tableau();
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  UnloadTexture(green_back);
  card_l.unload_textures();

  CloseWindow();

  return 0;
}

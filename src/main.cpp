#include <sys/types.h>
#include "../lib/fndtion.hpp"
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
  fndtion n_fnd;
  n_tab.tableau_init();
  Texture2D texture = LoadTexture("assets/coz1.png");
  Texture2D green_back = LoadTexture("assets/boardsol.png");
  Texture2D win_b = LoadTexture("assets/winb.png");
  bool on_title = true;
  float elasp_time = 0;
  int points = 0;
  SetTargetFPS(60);

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
                  SCREEN_HEIGHT / 2 - green_back.height / 2, WHITE);
      n_tab.draw_tableau();
      n_stock.draw_stock();
      n_fnd.draw_fnd();
      elasp_time += GetFrameTime();
      DrawText(TextFormat("Time: %.0f seconds", elasp_time), 58, 600, 20,
               WHITE);
      DrawText("UNDO", 58, 630, 20, WHITE);
    }
    if (n_fnd.is_win()) {
      DrawTexture(win_b, SCREEN_WIDTH / 2 - win_b.width / 2,
                  SCREEN_HEIGHT / 2 - win_b.height / 2, WHITE);
    }
    Vector2 mouse_pos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      std::cout << "X: " << mouse_pos.x << " Y: " << mouse_pos.y << std::endl;
    n_stock.stock_clicked(mouse_pos);
    n_tab.tableau_move(mouse_pos);
    n_tab.move_cards_frm_tab(n_fnd);
    n_tab.move_cards_frm_tab_tab();
    n_stock.waste_moved(mouse_pos);
    n_stock.move_cards_frm_sw(n_fnd);
    n_stock.move_cards_frm_wt(n_tab);
    EndDrawing();
  }

  UnloadTexture(texture);
  UnloadTexture(green_back);
  UnloadTexture(win_b);
  n_tab.unload_textures();
  n_stock.unload_textures();
  n_fnd.unload_textures();

  CloseWindow();

  return 0;
}

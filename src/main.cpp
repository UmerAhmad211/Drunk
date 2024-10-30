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
  InitAudioDevice();

  Music main_men = LoadMusicStream("assets/jazz.mp3");
  init card_l;
  card_l.load_textures();
  Sound win_sound = LoadSound("assets/game_win.wav");
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
  SetMusicVolume(main_men, 0.5f);
  PlayMusicStream(main_men);

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    if (on_title)
      UpdateMusicStream(main_men);

    if (on_title && IsKeyPressed(KEY_ENTER)) {
      on_title = false;
      StopMusicStream(main_men);
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (on_title) {
      DrawTexture(texture, SCREEN_WIDTH / 2 - texture.width / 2,
                  SCREEN_HEIGHT / 2 - texture.height / 2, WHITE);
      DrawText("Solitaire", 100, 300, 100, WHITE);
      DrawText("Press enter to continue.", 540, 640, 20, WHITE);

    } else if (!on_title) {
      DrawTexture(green_back, SCREEN_WIDTH / 2 - green_back.width / 2,
                  SCREEN_HEIGHT / 2 - green_back.height / 2, WHITE);
      n_tab.draw_tableau();
      n_stock.draw_stock();
      n_fnd.draw_fnd();
      elasp_time += GetFrameTime();
      DrawText(TextFormat("Time: %.0f seconds", elasp_time), 58, 600, 20,
               WHITE);
      DrawText(TextFormat("SCORE: %i", points), 58, 630, 20, WHITE);
    }
    if (n_fnd.is_win()) {
      PlaySound(win_sound);
      DrawTexture(win_b, SCREEN_WIDTH / 2 - win_b.width / 2,
                  SCREEN_HEIGHT / 2 - win_b.height / 2, WHITE);
      DrawText("YOU WON!", SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 70, 90,
               WHITE);
      DrawText(TextFormat("Time: %.0f seconds", elasp_time),
               SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 + 30, 50, WHITE);
      DrawText(TextFormat("SCORE: %i", points), SCREEN_WIDTH / 2 - 100,
               SCREEN_HEIGHT / 2 + 100, 50, WHITE);
    }
    Vector2 mouse_pos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      std::cout << "X: " << mouse_pos.x << " Y: " << mouse_pos.y << std::endl;
    n_stock.stock_clicked(mouse_pos, points);
    n_tab.tableau_move(mouse_pos);
    n_tab.move_cards_frm_tab(n_fnd, points);
    n_tab.move_cards_frm_tab_tab(points);
    n_stock.waste_moved(mouse_pos);
    n_stock.move_cards_frm_sw(n_fnd, points);
    n_stock.move_cards_frm_wt(n_tab, points);
    EndDrawing();
  }
  UnloadMusicStream(main_men);
  UnloadTexture(texture);
  UnloadTexture(green_back);
  UnloadTexture(win_b);
  UnloadSound(win_sound);
  n_tab.unload_textures();
  n_stock.unload_textures();
  n_fnd.unload_textures();

  CloseWindow();

  return 0;
}

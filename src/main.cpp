#include "../include/fndtion.hpp"
#include "../include/init.hpp"
#include "../include/stock.hpp"
#include "../include/tableau.hpp"
#include "raylib.h"
#include <sys/types.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define T_FPS 60
#define VOLUME 0.5f

int
main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Solitaire");
	InitAudioDevice();
	const Music &main_men = LoadMusicStream("assets/jazz.mp3");
	const Sound &win_sound = LoadSound("assets/game_win.wav");
	Init card_l;
	card_l.load_textures();
	card_l.shuffle_cards();
	card_l.init_cards_state();
	Stock n_stock(&card_l);
	Tableau n_tab(&card_l);
	Fndtion n_fnd;
	n_tab.tableau_init();
	Texture2D texture = LoadTexture("assets/coz1.png");
	Texture2D green_back = LoadTexture("assets/boardsol.png");
	Texture2D win_b = LoadTexture("assets/winb.png");
	bool on_title = true;
	float elasp_time = 0;
	int points = 0;
	SetMusicVolume(main_men, VOLUME);
	PlayMusicStream(main_men);
	SetTargetFPS(T_FPS);
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
			DrawTexture(texture,
				    SCREEN_WIDTH / 2 - texture.width / 2,
				    SCREEN_HEIGHT / 2 - texture.height / 2,
				    WHITE);
			DrawText("Solitaire", 100, 300, 100, WHITE);
			DrawText("Press enter to continue.", 540, 640, 20,
				 WHITE);
		} else if (!on_title && !n_fnd.is_win()) {
			DrawTexture(green_back,
				    SCREEN_WIDTH / 2 - green_back.width / 2,
				    SCREEN_HEIGHT / 2 - green_back.height / 2,
				    WHITE);

			n_tab.draw_tableau();
			n_stock.draw_stock();
			n_fnd.draw_fnd();
			elasp_time += GetFrameTime();

			DrawText(TextFormat("Time: %.0f seconds", elasp_time),
				 58, 600, 20, WHITE);
			DrawText(TextFormat("SCORE: %i", points), 58, 630, 20,
				 WHITE);
		}
		if (n_fnd.is_win()) {
			PlaySound(win_sound);
			DrawTexture(win_b, SCREEN_WIDTH / 2 - win_b.width / 2,
				    SCREEN_HEIGHT / 2 - win_b.height / 2,
				    WHITE);
			DrawText("YOU WON!", SCREEN_WIDTH / 2 - 200,
				 SCREEN_HEIGHT / 2 - 70, 90, WHITE);
			DrawText(TextFormat("Time: %.0f seconds", elasp_time),
				 SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 + 30,
				 50, WHITE);
			DrawText(TextFormat("SCORE: %i", points),
				 SCREEN_WIDTH / 2 - 100,
				 SCREEN_HEIGHT / 2 + 100, 50, WHITE);
		}
		Vector2 mouse_pos = GetMousePosition();
		n_stock.stock_clicked(mouse_pos, points);
		n_tab.tableau_move(mouse_pos);
		n_tab.move_cards_from_tab(n_fnd, points);
		n_tab.move_cards_from_tab_to_tab(points);
		n_stock.waste_moved(mouse_pos);
		n_stock.move_cards_from_stock_to_waste(n_fnd, points);
		n_stock.move_cards_from_waste_to_tableau(n_tab, points);
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

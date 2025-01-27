#include "raylib.h"

#include <iostream>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

#define SCREEN_WIDTH 434
#define SCREEN_HEIGHT 434

void UpdateDrawFrame(void);

int main() {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sudoku");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    UpdateDrawFrame();
  }
#endif

  CloseWindow();

  return 0;
}

void DrawHollowRect(int x, int y, int width, int height, int border,
                    Color border_color) {
  DrawRectangle(x, y, width, border, border_color);
  DrawRectangle(x, y, border, height, border_color);
  DrawRectangle(x + width - border, y, border, height, border_color);
  DrawRectangle(x, y + height - border, width, border, border_color);
}

void DrawHollowRect(int x, int y, int width, int height, Color border_color) {
  DrawHollowRect(x, y, width, height, 3, border_color);
}

void UpdateDrawFrame(void) {

  BeginDrawing();

  ClearBackground(RAYWHITE);

  DrawHollowRect(7, 7, SCREEN_WIDTH - 14, SCREEN_HEIGHT - 14, BLACK);

  int const DRAW_AREA_START_X = 10;
  int const DRAW_AREA_START_Y = 10;
  int const DRAW_AREA_WIDTH = SCREEN_WIDTH - 20;
  int const DRAW_AREA_HEIGHT = SCREEN_HEIGHT - 20;
  int const CELL_SIZE = DRAW_AREA_WIDTH / 9;
  int const CELL_BORDER = 1;

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int x = DRAW_AREA_START_X + i * CELL_SIZE;
      int y = DRAW_AREA_START_Y + j * CELL_SIZE;
      DrawHollowRect(x, y, CELL_SIZE, CELL_SIZE, CELL_BORDER, BLACK);
    }
  }

  EndDrawing();
}
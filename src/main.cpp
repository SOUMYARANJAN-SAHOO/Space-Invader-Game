#include <raylib.h>
#include "game.hpp"

int main()
{
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowHeight, windowWidth, "Space Invader");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawText("Space Invader", 10, 10, 20, WHITE);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}
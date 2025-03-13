#include <raylib.h>
#include "game.hpp"
#include "string"

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int zeros = width - numberText.length();
    return std::string(zeros, '0') + numberText;
}

int main()
{
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Space Invader");

    InitAudioDevice();

    Font font = LoadFontEx("assets/monogram.ttf", 64, 0, 0);
    Texture2D heartTexture = LoadTexture("assets/heart.png");

    SetTargetFPS(60);

    Game game;


    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(DARKGRAY);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, YELLOW);
        DrawLineEx({25, 730}, {775, 730}, 3, YELLOW);

        if(game.run){
            DrawTextEx(font, "Level 01", {570, 740}, 34, 2, YELLOW);
        }else{
            DrawTextEx(font, "Game Over", {570, 740}, 34, 2, YELLOW);
        }

        float x = 50;
        for (int i = 0; i < game.GetLives(); i++){
            DrawTextureV(heartTexture, {x, 740}, WHITE);
            x += 50;
        }

        DrawTextEx(font , "SCORE", {50, 15}, 34, 2, YELLOW);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 50}, 34, 2, YELLOW);

        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, YELLOW);
        std::string highscoreText = FormatWithLeadingZeros(game.highsScore, 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, YELLOW);

        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}
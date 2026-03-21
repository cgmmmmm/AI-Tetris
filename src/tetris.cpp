#include <raylib.h>
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main() 
{
    InitWindow(500, 620, "Tetris"); // x, y, windowName
    
    SetTargetFPS(60);

    Font font = LoadFontEx("src/Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false) 
    {
        game.HandleInput();
        
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(charcoalBlue);
        // void DrawTextExt(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);
        DrawTextEx(font, "Next", {370, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Score", {360, 265}, 38, 2, WHITE);
        DrawTextEx(font, "Highest", {340, 370}, 38, 2, WHITE);
        DrawTextEx(font, "Controls", {330, 500}, 38, 2, WHITE);
        DrawTextEx(font, "A: Left", {330, 530}, 25, 2, WHITE);
        DrawTextEx(font, "D: Right", {330, 550}, 25, 2, WHITE);
        DrawTextEx(font, "R: Rotate", {330, 570}, 25, 2, WHITE);
        // void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);
        DrawRectangleRounded({320, 55, 170, 180}, 0.3, 6, darkGrey);
        DrawRectangleRounded({320, 305, 170, 60}, 0.3, 6, darkGrey);
        DrawRectangleRounded({320, 415, 170, 60}, 0.3, 6, darkGrey);
        
        game.Draw();

        if (game.gameOver)
        {
            DrawRectangleRounded({20, 250, 280, 120}, 0.3, 6, {0, 0, 0, 180});
            DrawTextEx(font, "GAME OVER", {68, 270}, 40, 2, WHITE);
            DrawTextEx(font, "PRESS [SPACE] TO RESTART", {35, 320}, 18, 2, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}
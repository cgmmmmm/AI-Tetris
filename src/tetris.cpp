#include <raylib.h>
#include "game.h"

int main() 
{
    Color NAVYBLUE = {0, 0, 128, 255}; // r,g,b,a

    InitWindow(300+1, 600+1, "Tetris"); // x, y, windowName
    
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false) 
    {
        game.HandleInput();
        
        BeginDrawing();
        ClearBackground(NAVYBLUE);
        
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
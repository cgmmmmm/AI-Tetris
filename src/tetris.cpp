#include <raylib.h>
#include "game.h"

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
    Color NAVYBLUE = {0, 0, 128, 255}; // r,g,b,a

    InitWindow(300+1, 600+1, "Tetris"); // x, y, windowName
    
    SetTargetFPS(60);

    Game game = Game();

    while (WindowShouldClose() == false) 
    {
        game.HandleInput();
        
        if (EventTriggered(0.2))
        {
            game.MoveBlockDown();
        }
        
        BeginDrawing();
        ClearBackground(NAVYBLUE);
        
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}
#include <raylib.h>
#include "grid.h"
#include "blocks.cpp"

int main() 
{
    Color NAVYBLUE = {0, 0, 128, 255}; // r,g,b,a

    InitWindow(300+1, 600+1, "Tetris"); // x, y, windowName
    
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.Print(); // for testing purposes

    TBlock block = TBlock();

    while (WindowShouldClose() == false) 
    {
        BeginDrawing();
        ClearBackground(NAVYBLUE);

        grid.Draw();
        block.Draw();
        
        EndDrawing();
    }

    CloseWindow();
}
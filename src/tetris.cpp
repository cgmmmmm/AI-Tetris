#include <raylib.h>
#include "grid.h"

int main() 
{
    Color NAVYBLUE = {0, 0, 128, 255}; // r,g,b,a

    InitWindow(300+1, 600+1, "Tetris"); // x, y, windowName
    
    SetTargetFPS(60);

    Grid grid = Grid();
    // testing
    grid.grid[0][0] = 1;
    grid.grid[1][0] = 2;
    grid.grid[2][0] = 3;
    grid.grid[3][0] = 4;
    grid.grid[4][0] = 5;
    grid.grid[5][0] = 6;
    grid.grid[6][0] = 7;
    grid.Print(); // for testing purposes

    while (WindowShouldClose() == false) 
    {
        BeginDrawing();
        ClearBackground(NAVYBLUE);

        grid.Draw();
        
        EndDrawing();
    }

    CloseWindow();
}
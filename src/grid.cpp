#include <iostream>
#include "grid.h"
#include "colors.h"

Grid::Grid() 
{
    numRows = 20;
    numCols = 10;
    cellSize = 30;

    Initialize();

    colors = GetCellColors();
}

void Grid::Initialize() 
{
    for (int row=0; row<numRows; row++) 
    {
        for (int col=0; col<numCols; col++) 
        {
            grid[row][col] = 0;
        }
    }
}

void Grid::Print()
{
    for (int row=0; row<numRows; row++) 
    {
        for (int col=0; col<numCols; col++) 
        {
            std::cout << grid[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for (int row=0; row<numRows; row++) 
    {
        for (int col=0; col<numCols; col++)
        {
            int cellValue = grid[row][col];
            // void DrawRectangle(int posX, int posY, int width, int height, Color color)
            // the reason for the +1 is to add a 1px offset of rectangle
            // the reason for the -1 is to add a margin for each cell
            // the +1 and -1 is so that we can see the grid
            DrawRectangle(col * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize - 1, colors[cellValue]);
        }
    }
}

bool Grid::IsCellOutside(int row, int col)
{
    if (row >= 0 && row < numRows && col >= 0 && col < numCols)
    {
        return false;
    }
    return true;
}

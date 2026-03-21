#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    void Draw();
    void Move(int rows, int cols);
    void Rotate();
    void UndoRotation();

    int id;

    // map<rotationState, BlockPosition>
    std::map<int, std::vector<Position>> cells;

    std::vector<Position> GetCellPositions();

private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;

    int rowOffset;
    int colOffset;
};
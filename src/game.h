#pragma once

#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();

    void Draw();
    void HandleInput();

    void MoveBlockDown();
    void MoveBlockLeft();
    void MoveBlockRight();

    Grid grid;

private:
    bool IsBlockOutside();

    std::vector<Block> blocks;

    Block currentBlock;
    Block nextBlock;
};
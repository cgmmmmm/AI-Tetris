#include <random>
#include "game.h"

Game::Game()
{
    grid = Grid();

    blocks = GetAllBlocks();

    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();
    
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.Draw();
    currentBlock.Draw();
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    switch (keyPressed)
    {
        case KEY_A:
            MoveBlockLeft();
            break;

        case KEY_D:
            MoveBlockRight();
            break;

        case KEY_S:
            MoveBlockDown();
            break;

        case KEY_R:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockDown()
{
    currentBlock.Move(1, 0);

    if (IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.Move(-1, 0);
        LockBlock();
    }
}

void Game::MoveBlockLeft()
{
    currentBlock.Move(0, -1);

    if (IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.Move(0, 1);
    }
}

void Game::MoveBlockRight()
{
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.Move(0, -1);
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.col))
        {
            return true;
        }
    }
    
    return false;
}

void Game::RotateBlock()
{
    currentBlock.Rotate();

    if (IsBlockOutside() || BlockFits() == false)
    {
        currentBlock.UndoRotation();
    }
}

void Game::LockBlock()
{
    std::vector<Position> tiles = currentBlock.GetCellPositions();

    for (Position item : tiles)
    {
        grid.grid[item.row][item.col] = currentBlock.id;
    }
    currentBlock = nextBlock;
    nextBlock = GetRandomBlock();

    grid.ClearFullRows();
}

bool Game::BlockFits()
{
    std::vector <Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.col) == false)
        {
            return false;
        }
    }
    return true;
}
#pragma once

#include <fstream>
#include "include/json.hpp"

#include "grid.h"
#include "blocks.cpp"

using json = nlohmann::json;

class Game
{
public:
    Game();
    ~Game();

    void Draw();
    void HandleInput();

    void MoveBlockDown();

    bool gameOver;

    int score;
    int highScore;
    int gamesPlayed;

    Music music;

private:
    bool IsBlockOutside();

    void RotateBlock();

    void LockBlock();

    bool BlockFits();

    void Reset();

    void UpdateScore(int linesCleared, int moveDownPoints);

    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();

    void MoveBlockLeft();
    void MoveBlockRight();

    std::vector<Block> blocks;

    Block currentBlock;
    Block nextBlock;

    Grid grid;

    Sound rotateSound;
    Sound clearSound;

    void LoadHighScore();
    void SaveHighScore();
};
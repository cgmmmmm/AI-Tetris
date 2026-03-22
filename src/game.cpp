#include <random>
#include "game.h"

Game::Game()
{
    grid = Grid();

    blocks = GetAllBlocks();

    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

    gameOver = false;
    
    score = 0;

    LoadHighScore();

    InitAudioDevice();
    music = LoadMusicStream("src/Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("src/Sounds/rotate.mp3");
    clearSound = LoadSound("src/Sounds/clear.mp3");
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
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
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
        case 3:
            nextBlock.Draw(255, 130);
            break;
        case 4:
            nextBlock.Draw(255, 120);
            break;
        default:
            nextBlock.Draw(270, 110);
            break;
    }
}

void Game::HandleInput()
{
    int keyPressed = GetKeyPressed();

    if (gameOver && keyPressed == KEY_SPACE)
    {
        gameOver = false;
        Reset();
    }

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
            UpdateScore(0,1);
            break;

        case KEY_R:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver) 
    {
        currentBlock.Move(1, 0);

        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

void Game::MoveBlockLeft()
{   
    if (!gameOver)
    {
        currentBlock.Move(0, -1);

        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
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
    if (!gameOver)
    {
        currentBlock.Rotate();

        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
        else
        {
            PlaySound(rotateSound);
        }
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
    if (BlockFits() == false)
    {
        gameOver = true;
        gamesPlayed++;
        SaveHighScore();
    }
    nextBlock = GetRandomBlock();

    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
        PlaySound(clearSound);
        UpdateScore(rowsCleared, 0);
    }
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

void Game::Reset()
{
    grid.Initialize(); // clear the grid

    // select the new game first block
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();

    score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
    switch(linesCleared)
    {
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 1000;
            break;
        default:
            break;
    }

    score += moveDownPoints;

    if (score > highScore)
    {
        highScore = score;
    }
}

void Game::LoadHighScore() 
{
    std::ifstream file("data/stats.json");
    if (file.is_open()) 
    {
        json j;
        file >> j;
        highScore = j.value("highScore", 0);
        gamesPlayed = j.value("gamesPlayed", 0);
        file.close();
    }
    else
    {
        highScore = 0;
        gamesPlayed = 0;
    }
}

void Game::SaveHighScore() 
{
    json j;
    j["highScore"] = highScore;
    j["gamesPlayed"] = gamesPlayed;

    std::ofstream file("data/stats.json");
    if (file.is_open())
    {
        file << j.dump(4); // add 4-space indentation
        file.close();
    }
}
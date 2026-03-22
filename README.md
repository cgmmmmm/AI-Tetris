# AI Tetris (C++ + Raylib + Machine Learning)

<br>

## Overview
AI Tetris is a two-phase project that combines **game development** and **machine learning**:

1. **Game Development** — Build a complete Tetris game from scratch using **C++** and **raylib**
2. **AI Training** — Train a machine learning model to play the game autonomously

This project is designed as a **learning-focused engineering journey**, covering:
- Low-level game architecture
- Real-time rendering and input handling
- State management and collision systems
- AI decision-making and optimization

<br>

---

<br>

## Objectives

- Understand how a game loop works at a systems level
- Implement Tetris mechanics from scratch (no game engines)
- Design clean, modular C++ code
- Build a simulation environment suitable for AI training
- Train and evaluate an AI model to play Tetris

<br>

---

<br>

## Tech Stack

### Core
- **Language:** C++
- **Graphics Library:** raylib

### AI / ML
- Python (for training)
- NumPy / PyTorch / TensorFlow (TBD)
- C++ & Python integration (file I/O or API)

<br>

---

<br>

## Tetris Game Development

Credit and inspiration for this project go to **Programming With Nick**'s youtube video, titled [***"Creating Tetris in C++ with raylib - Beginner Tutorial (OOP)"***](https://www.youtube.com/watch?v=wVYKG_ch4yM&t=246s). Which provided a structured guide for the game's development.

The game will be built step-by-step to ensure full understanding of each system.

#### 1. Setup Game Loop 
* Event Handling
* Updating Positions
* Drawing Objects

#### 2. Creating the Grid 
* In Tetris, the gameplay area is a 20rows*10columns grid.
* Blocks will fall down the grid, player must arrange the blocks and form complete rows.
* The origin cell is the top-left cell, having the coordinate (0,0).
* To represent the grid, we will use a two-dimensional array.
* Empty cells is represented with a value of 0.
* When a block is permanently placed on the grid by the player, the corresponding cells will be assigned a value reflecting its color.
* Since there are 7 colors in the game, the values used in the 2D array will range from 0 to 7. 
    * 0 for empty cells.
    * 1-7 for the colors of the blocks.
* The current block that can still be controlled by the player will not be reflected in the array. The block will instead be stored and managed separately in the game logic.

#### 3. Creating the Blocks 
* The blocks of the game all consists of 4 tiles, coming in different shapes like:
    * L-Block
    * J-Block
    * I-Block
    * O-Block
    * S-Block
    * T-Block
    * Z-Block
* These blocks can spin around, usually in the middle of one of the tiles.
* For each of the four rotation states, we store which cells are occupied in a specific grid, not all the cells of the grid.
* For example, take a T-Block:
    1. A grid is drawn around the T-block that fits the block. (grid is 3x3, making it 9 cells in total in the grid)
    2. However, we only need to store the cells that the T-block occupies, not the whole grid.
    3. If the T-block is in Rotation State 0 (no rotation), we only need to store the values: [(0,1), (1,0), (1,1), (1,2)]
    4. If the T-block is in Rotation State 1 (clockwise 90deg rotation along the middle cell), we only need to store the values: [(0,1), (1,1), (1,2), (2,1)]. And so on...
    5. Using the bounding grid approach to represent the blocks has a big advantage: it makes rotating the blocks much easier.
    6. To rotate a block, all we need to do is to update a state variable that indicates the current rotation state of the block, and modify the occupied cells stored in the grid accordingly.
    7. This approach saves computational time and complexity by not needing to calculate the new positions of each tile in the block.

#### 4. Move the Blocks 
* Up until this point, we are displaying only the occupied positions of a smaller grid, which is the 3x3 block-grid.
* The origin of the 3x3 block-grid is at the top-left corner.
* So if we want to move the block, all we have to do is move its origin point (the top-left corner of the 3x3 block-grid).
* For example, if we want to move the block X rows down, and Y columns to the right, we just need TWO(2) variables to hold the offset in the x and y-axis on the grid. 
    * `rowOffset`
    * `colOffset`
* To move X rows down and Y columns to the right or left, we adjust the `rowOffset = X` and `colOffset = ±Y`, and add these values to the row and column positions of the block's origin point.
* The ability to move the block also gave rise to an issue, the block can move outside the game grid, beyond the game window.
* Since we know the game grid is 20x10, the solution is to check the current position of each tile of the block. If any of the tiles has moved outside of the game window, we need to move it back within the boundary of the game window.

#### 5. Rotate the Blocks 
* Since we already have all the positions of the blocks in every rotation state, we can simply create a member function `RotateBlock()` in the game class in the header file, and implement the function in the implementation file.
* This however gives rise to another issue, our block could be rotated to an invalid position outside the game window.
* Fixing this issue is very straightforward, using the same principle that is used in checking if the block moves outside the game window. If the block rotates to an invalid position outside the game window, simply undo the rotation.

#### 6. Check for Collisions 
* Tetris is a game where the blocks falls automatically, until it hits the bottom of the game grid (X, 20), so we have to implement the automatic dropping of the block first.
* To achieve this, we can call the `MoveBlockDown()` method of the game class in the game loop. Then, create and using the function `EventTriggered()` that will be used to check if a certain amount of time has passed since the end of the previous event. We can use `EventTriggered()` function to control the event updating rate (time interval between start and end of an event), and repeatedly calls the `MoveBlockDown()` method every few milliseconds.
* However, there is another issue that we need to address. That is to not allow anymore movements after a collision with the bottom of the game grid.
* To address this issue, we create the `LockBlock()` private function in the game class. The method need to update the game grid values to represent the location of each cell of the block on the grid at the time it touches the bottom of the screen. For each cell, we will store the ID (corresponding to the block's color) of the block, in the corresponding cell on the game grid. This will mark the cells as locked and indicate that the block has reached its final position. And the next random block can proceed.
* However, this also creates another issue where the block will always reach the bottom of the game grid, even when there is a block present.
* To fix this issue, we can create `IsCellEmpty()` method to check if a cell of the grid is empty or not. Then, implement `BlockFits()` to check every cell of a block to see if it is on top of an empty cell of the grid or not.
* Now, if we attempt to move the block down and encounter a cell that is already occupied, we undo the move and lock the block in place.
* Again, this introduces a small problem, currently we only check if a block will collide with another block only when the block is moving down, this will cause the current block to overwrite a locked block by moving the current block left, right, or during any rotating state. 
* Since we now have a function needed to check if a block fits in its new position. The fix is to implement that in `MoveBlockLeft()`, `MoveBlockRight()`, and `RotateBlock()` as well.

#### 7. Check for Completed Rows 
* To check for completed rows, all we have to do is check if a row is full, and when it is, we have to clear the row and move all the occupied above the row one row down.
* To do this, we scan every row of the grid from the bottom to the top. We can use a variable `completedRow` to hold the number of completed rows. If there is a completed row, `completedRow++`, then clear the row and check the next row. If the next row is not completed, we move the every row down by the value of `completedRow` variable until we reach the bottom of the game grid.

#### 8. Game Over
* In Tetris, the game ends when a newly spawned block overlaps with a block that is already locked in place on the grid, preventing further movement or placement of a new block.
* To check if the game has to end, we have to check if the newly created block fits in the grid, if it does not fit, the game is over.
* Now, we need to make the game restart when it's over.

#### 9. Create a User Interface 
* The user interface consists of several components:
    * Canvas
    * Score title text, score value box, and score value.
    * Next block title text, next block box, and next block display.
    * Game Over display.
    * Instructions on how to play the game (Controls)

#### 10. Add Scores 
* The scoring system for this custom Tetris game is limited for simplicity.
* The goal of this Tetris game is to train a ML model to play the game autonomously and experiment from there. A simplified Tetris game can help reduce training complexity.
* This Tetris game scoring system is as following:
    * 100 points for a single line clear
    * 300 points for a double line clear
    * 500 points for a triple line clear
    * 1,000 points for a quadruple line clear 
    * 1 point for each block moved down by player

#### 11. Add Next Block 
* Since we already have a `Draw()` method that draws a block on the screen, we will reuse the `Draw()` method.
* We need to draw the block, but inside the Next box.

#### 12. Add Sounds
* To add the sounds and music, use the `InitAudioDevice()` provided by the raylib library.
* We can use `LoadMusicStream()`, `PlayMusicStream()`, `UpdateMusicStream()` to load, play, and update the music.
* Additionally, we can use `LoadSound()` and `PlaySound()` to to play the sounds. 
* Don't forget to unload the sounds and music using a destructor and `CloseAudioDevice()`, `UnloadSound()`, `UnloadMusicStream` to free memory. When you load an audio file, the game allocates system memory to hold that data. If it isn't unloaded, especially when changing game states or closing the game, that memory remains occupied, which can lead to memory leaks and cause the game to slow down or crash over time.

#### 13. High Score & Stats
* To save the high score, we can store it in a JSON object `stats.json`. We use the single-header nlohmann/json C++ library to handle the parsing and serialization.
* When the game initializes, a `LoadHighScore()` method opens an input file stream (`std::ifstream`). It reads the `stats.json` file, parses the JSON structure, and extracts `"highScore"` integer into a variable in RAM. If the file doesn't exist (like on the first playthrough), it safely defaults to a score of 0.
* Writing data to a hard drive during active gameplay is slow and can cause frame drops or stuttering. To optimize performance, we only update the `highScore` variable in RAM while the game is running, continuously comparing it against the player's current score.
* We only execute a disk write operation when the game actually ends. We create a temporary JSON object, map the `highScore` integer to it, and use an output file stream (`std::ofstream`) to overwrite `stats.json` file,
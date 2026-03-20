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
#### 6. Check for Collisions 
#### 7. Check for Completed Rows 
#### 8. Game Over 
#### 9. Create a User Interface 
#### 10. Add Scores 
#### 11. Add Next Block 
#### 12. Add Sounds


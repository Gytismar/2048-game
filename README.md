# 2048-game
## About
Recreation of the popular game 2048, written in C++ and using the SFML library for graphics.

You can play vs an AI, another player or just watch two AI compete.

The game has a special ability, that removes all 2 and 4 tiles.
## Controls
### Menu
* **↑ and ↓** to navigate the menu options.
* **Enter** to select

### Player vs AI
* **W or ↑** to move tiles up
* **S or ↓** to move tiles down
* **A or ←** to move tiles left
* **D or →** to move tiles right
* **X** to use special ability (remove all 2 and 4 tiles if possible)
* **R** return to menu

### Player vs Player
#### Player1 (left window)
* **W** to move tiles up
* **S** to move tiles down
* **A** to move tiles left
* **D** to move tiles right
* **X** to use special ability (remove all 2 and 4 tiles if possible)
* **R** return to menu

#### Player2 (right window)
* **↑** to move tiles up
* **↓** to move tiles down
* **←** to move tiles left
* **→** to move tiles right
* **M** to use special ability (remove all 2 and 4 tiles if possible)
* **R** return to menu

### AI showcase
* **R** return to menu

## Known issues
* The AI almost always loses if the grid is smaller than 5x5, but usually wins if the grid is 5x5 or larger
* The AI sometimes freezes at the start of the game
* The AI sometimes appears to be able to move, but dosen't, because it would lose
* The AI may be frozen for a while before it admits defeat

# FangMichSpiel

This is a simple C++ game developed using Qt, where the player has to catch a button that moves randomly across the screen within a limited time frame.

## Game Mechanics

- The game has a fixed window size of 800x600 pixels.
- A button randomly moves to a new position every second.
- The player has 2 minutes (120 seconds) to catch the button by clicking on it.
- The game ends when either:
  - The player scores 10 points (they win).
  - The time runs out (the player loses).
- The player's score and the remaining time are displayed on the screen.

## How to run

1. Install [Qt](https://www.qt.io/download) (if not already installed).
2. Open the `fangmichspiel.pro` file in Qt Creator.
3. Build and run the project within Qt Creator.

## Technologies used

- **C++**: Core language for game logic.
- **Qt**: Used for GUI (QMainWindow, QPushButton, QLabel, QTimer).
- **QTimer**: To control button movement and game time.
- **QMessageBox**: For end-game notifications (win/loss).

## Game Features

- Random button movement across the game window every second.
- Countdown timer with a 2-minute limit.
- Score tracking: the player needs to reach 10 points to win.
- End-game messages for both winning and losing conditions.

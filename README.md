# Terminal Pong Game in C

A simple Pong game implemented in C, playable in your terminal using ASCII graphics and the [ncurses](https://invisible-island.net/ncurses/) library!

## Features

- Classic Pong gameplay
- Play against a basic AI
- Terminal-based ASCII graphics
- Responsive controls using arrow keys
- Lightweight and fast

## Requirements

- GCC or any C compiler
- [ncurses library](https://invisible-island.net/ncurses/) (pre-installed on most Linux/macOS systems)

## Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/YOUR_USERNAME/YOUR_REPO_NAME.git
   cd YOUR_REPO_NAME
   ```

2. **Install ncurses (if not already installed):**

   - **Ubuntu/Debian:**
     ```sh
     sudo apt-get install libncurses5-dev
     ```
   - **macOS (Homebrew):**
     ```sh
     brew install ncurses
     ```

3. **Compile the game:**
   ```sh
   gcc pong.c -o pong -lncurses
   ```

## How to Play

1. **Run the game:**
   ```sh
   ./pong
   ```

2. **Controls:**
   - **Up Arrow (↑):** Move paddle up
   - **Down Arrow (↓):** Move paddle down
   - **q:** Quit the game

3. **Gameplay:**
   - Your paddle is on the left; AI is on the right.
   - Try to hit the ball back each time it comes to your side.
   - The first to score the most points wins!

## Project Structure

```
pong.c        # Main source code
README.md     # This file
```

## Credits

- Made by [YOUR NAME or USERNAME](https://github.com/YOUR_USERNAME)
- Inspired by the classic Pong arcade game

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more information.

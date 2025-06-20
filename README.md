# Terminal Pong Game in C

A simple Pong game implemented in C, playable in your terminal using ASCII graphics and the [ncurses](https://invisible-island.net/ncurses/) library

## Features

- Classic Pong gameplay
- Play against a basic AI
- Terminal-based ASCII graphics
- Responsive controls using arrow keys
- Lightweight and fast

## Requirements

- GCC or any C compiler

## Installation

1. **Clone the repository:**
   ```sh
   git clone https://github.com/srashadddd/pong-game.git
   cd pong-name
   ```

2. **Compile the game:**
   ```sh
   gcc pong.c -o pong
   ```

## How to Play

1. **Run the game:**
   ```sh
   ./pong
   ```

2. **Controls:**
   - **W:** Move paddle up
   - **S:** Move paddle down
   - **Q:** Quit the game

3. **Gameplay:**
   - Your paddle is on the left; AI is on the right.
   - Try to hit the ball back each time it comes to your side.
   - The first to score the most points wins

## Project Structure

```
pong.c        # Main source code
README.md     # This file
```

## Credits

- Made by [Srashad](https://github.com/srashadddd)
- Inspired by the classic Pong arcade game

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for more information.

# Rock, Paper, Scissors - doodle edition

A small C++ desktop game with a hand-drawn, paper-and-ink look. Pick a move by
clicking one of the sketchy cards or pressing `1`, `2`, or `3`. Round results
appear with a typewriter-style reveal, and the score stays on screen. On macOS,
the interface uses the built-in Chalkduster font when available. Press `R` to
reset the score or `Esc` to quit.

## Requirements

- A C++17 compiler
- CMake 3.16 or newer
- [raylib](https://www.raylib.com/)

On macOS with Homebrew:

```sh
brew install cmake raylib
```

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/rps_game
```

The project is split into the game logic (`game_logic.cpp`), the raylib
interface (`input_ui.cpp`), and the application loop (`main.cpp`).

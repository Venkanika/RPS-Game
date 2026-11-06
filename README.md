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

## About the Project
A multi-file Rock, Paper, Scissors desktop game developed in C++ using Raylib. The project is split into distinct modules to keep the rendering interface separate from the core game rules and to allow our team to collaborate concurrently via GitHub.

## Team Contributions
* **Kanika**: Set up the GitHub repository, managed project collaboration/merges, and developed `main.cpp` along with the shared header file (`rock_paper_scissors.h`).
* **Kimleap**: Built the graphical user interface (`input_ui.cpp`), handling window layout, button click detection, and procedural rendering.
* **Prasith**: Implemented the core game engine (`game_logic.cpp`), including the random computer move generator and win/loss/tie evaluation logic.
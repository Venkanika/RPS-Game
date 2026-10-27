# Rock-Paper-Scissors (C++)

A simple command-line Rock-Paper-Scissors game built in C++ for our group project[cite: 1]. The codebase is split across multiple files so our team could work on separate parts simultaneously using Git[cite: 1].

## How It's Organized
- `rock_paper_scissors.h`: Common header file with shared function prototypes[cite: 1].
- `input_ui.cpp`: Prompts the user, validates input ('r', 'p', 's'), and prints choices[cite: 1].
- `game_logic.cpp`: Generates the computer's random move and decides the winner[cite: 1].
- `main.cpp`: Runs the overall game flow from start to finish[cite: 1].

## How to Build and Run

Compile all source files together using `g++`:

```bash
g++ main.cpp input_ui.cpp game_logic.cpp -o rps_game
./rps_gameh ```bash

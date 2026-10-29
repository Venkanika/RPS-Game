#ifndef ROCK_PAPER_SCISSORS_H
#define ROCK_PAPER_SCISSORS_H

enum class Move {
    None,
    Rock,
    Paper,
    Scissors
};

enum class RoundResult {
    Win,
    Loss,
    Draw
};

struct GameState {
    Move playerMove = Move::None;
    Move computerMove = Move::None;
    RoundResult result = RoundResult::Draw;
    int wins = 0;
    int losses = 0;
    int draws = 0;
    int rounds = 0;
    float resultRevealTime = 0.0f;
    bool hasPlayed = false;
};

Move getComputerChoice();
RoundResult determineWinner(Move playerMove, Move computerMove);
const char* moveName(Move move);
void initializeGameUi();
void updateGameUi(GameState& state, float deltaTime);
void drawGameUi(const GameState& state, float elapsedTime);
void shutdownGameUi();

#endif

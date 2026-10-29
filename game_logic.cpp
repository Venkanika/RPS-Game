#include "rock_paper_scissors.h"
#include <random>
using namespace std;

Move getComputerChoice() {
    static mt19937 generator(random_device{}());
    static uniform_int_distribution<int> distribution(0, 2);
    return static_cast<Move>(distribution(generator) + 1);
}

RoundResult determineWinner(Move playerMove, Move computerMove) {
    if (playerMove == computerMove) {
        return RoundResult::Draw;
    }

    const bool playerWins =
        (playerMove == Move::Rock && computerMove == Move::Scissors) ||
        (playerMove == Move::Paper && computerMove == Move::Rock) ||
        (playerMove == Move::Scissors && computerMove == Move::Paper);
    return playerWins ? RoundResult::Win : RoundResult::Loss;
}

const char* moveName(Move move) {
    switch (move) {
        case Move::Rock:
            return "rock";
        case Move::Paper:
            return "paper";
        case Move::Scissors:
            return "scissors";
        case Move::None:
            return "";
    }
    return "";
}

#include <cstdlib>
#include <iostream>
#include "rock_paper_scissors.h"

using namespace std;

char getComputerChoice();
void chooseWinner(char playerChoice, char computerChoice);

/*
============ Overview =============
This file determines the computer's
choice in rock-paper-scissors and
decides the winner by comparing 
computer output and player input.

rock    == 'r'
paper   == 'p'
scissor == 's'
===================================
*/

char getComputerChoice() {
    // Computer makes a random choice between 1 - 3
    srand(time(NULL));
    const int RANGE = 3;
    const int MINIMUM = 1;
    int choice = (int)(random()*RANGE) + MINIMUM;

    // returns a (char) value to be compared with the player's choice
    switch (choice) {
        case 1:
            return 'r'; 
        case 2: 
            return 'p'; 
        case 3:
            return 's'; 
        default:
            return -1;
    }
}

void chooseWinner (char playerChoice, char computerChoice) {
    // Takes playerChoice and compares with computerChoice to decide the winner
    switch (playerChoice) {
        case 'r': 
            if (computerChoice == 'r') {
                cout << "DRAW!\n";
            } 
            else if (computerChoice == 'p') {
                cout << "YOU LOSE!\n";
            } 
            else { // computerChoice == 's'
                cout << "YOU WIN!";
            }
            break;
        case 'p': // Player h
            if (computerChoice == 'p') {
                cout << "DRAW!\n";
            } 
            else if (computerChoice == 's') {
                cout << "YOU LOSE!\n";
            } 
            else { // computerChoice == 'r'
                cout << "YOU WIN!";
            }
            break;
        case 's':
            if (computerChoice == 's') {
                cout << "DRAW!\n";
            } 
            else if (computerChoice == 'r') {
                cout << "YOU LOSE!\n";
            } 
            else { // computerChoice == 'p'
                cout << "YOU WIN!";
            }
            break;
    }
}
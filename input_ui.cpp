#include <iostream> 
#include <rock_paper_scissors.h>
using namespace std; 

char userChoice(){
    char player; 
    cout << "Rock, Paper, Scissors Game Start!" << endl;
    cout << "Please Input the following: " << endl; 
    cout << "r: Rock" << endl; 
    cout << "p: Paper" << endl; 
    cout << "s: Scissor" << endl; 
    cin >> player; 

    while ( (player!= 'R') || (player != 'P') || (player != 'S')  ) {
    cout << "Please Input the following only!! " << endl; 
    cout << "r: Rock" << endl; 
    cout << "p: Paper" << endl; 
    cout << "s: Scissor" << endl; 
    cin >> player; 
    }
    return player;
}

void showChoice(char choice){
    switch (choice) {
        case 'r': 
            cout << "Rock" << endl;
            break; 
        case 'p':
            cout << "Paper" << endl; 
            break;
        case 's':
            cout << "Scissor"<< endl;
            break;
    }
}


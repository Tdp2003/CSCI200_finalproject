/* CSCI 200: Final Project
 *
 * Author: Tyler Pina
 * Resources used: none
 *
 * This program simulates a baseball game between two different teams and will print to the console the winner of the game
 * as well as individual events that happen during the game, like a hit or an out. Any lineup can be inputted into the 
 * simulator by placing player names and ratings into the correct file. The user can also customize the number of innings
 * that they want to be simulated, excluding potential extra inning scenarios.
 */

#include "Team.h"
#include "Game.h"
#include <iostream>
using namespace std;

int main(){
    srand(time(0));
    rand();

    //create home team
    Team* pHome = new Team(true);
    if(!pHome->formTeam()){
        //if the file cannot be opened, -1 will be returned
        return -1;
    }
    
    //create away team
    Team* pAway = new Team(false);
    if(!pAway->formTeam()){
        //if the file cannot be opened, -1 will be returned
        return -1;
    }

    int numInnings = 0;
    while(numInnings < 1){
        cout << "How many innings would you like to play? ";
        cin >> numInnings;
    }

    //create game object and play the game
    Game* pGame = new Game();
    pGame->setInningsToPlay(numInnings);
    pGame->playGame(pHome,pAway);
    pGame->printWinner(pHome, pAway);
    
    return 0;
}
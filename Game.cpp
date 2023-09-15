#include "Game.h"
#include <iostream>
#include <ctime>

using namespace std;

Game::Game(){
    mInning = 1;
    mHScore = 0;
    mAScore = 0;
    mHLineupPos = 0;
    mALineupPos = 0;
    mTop = true;
    mInningsToPlay = 9;
    mNumOuts = 0;
}

void Game::playGame(Team* pHomeTeam, Team* pAwayTeam){
    //check to make sure that the two teams have players in their lineup arrays
    if(pHomeTeam->getPlayers()->getSize() == 0 || pAwayTeam->getPlayers()->getSize() == 0){
        return;
    }
    //while the inning is less than 10, normal innings will be played
    while(mInning <= mInningsToPlay){
        cout << "------------------------------" << endl;
        if(mTop){
            cout << "It is the top of the " << mInning << " inning!" << endl;
            playInning(pAwayTeam);
            mTop = false;
        }else{
            if(mHScore > mAScore && mInning == mInningsToPlay){
                return;
            }
            cout << "It is the bottom of the " << mInning << " inning!" << endl;
            playInning(pHomeTeam);
            mInning++;
            mTop = true;
        }
    }
}

void Game::playInning(Team* pTeam){
    int randNum = 0;
    //the inning will continue to be played until the number of outs equals 3
    while(mNumOuts < 3){
        //at bat
        if(mTop){
            //random number generation to determine the outcome of each individual's at bat
            //the higher a players rating, the more likely they are to get a hit
            randNum = rand() % (16 - pTeam->getPlayers()->get(mALineupPos)->getRating()) + pTeam->getPlayers()->get(mALineupPos)->getRating();
            if(randNum >= 12){
                //if the first random number is greater than 11, the player got a hit
                //the next random number will determine the type of hit that the player got
                randNum = rand() % 11;
                if(randNum <= 6){
                    handleHit(pTeam,1, mALineupPos);
                }else if(randNum <= 8){
                    handleHit(pTeam,2, mALineupPos);
                }else if(randNum == 9){
                    handleHit(pTeam,3, mALineupPos);
                }else{
                    handleHit(pTeam,4,mALineupPos);
                }
            }else{
                //if the number is less than 12, the player is out
                mNumOuts++;
                handleOut(pTeam, mALineupPos);
            }
            //after each at bat, the lineup position is incremented to get to the next player
            mALineupPos++;
            if(mALineupPos == 9){
                //in this case, the end of the lineup is reached, so the position resets to 0
                mALineupPos = 0;
            }
        }else{
            if(mInning > mInningsToPlay && mHScore > mAScore){
                //as per baseball rules, if the home team is winning after the top of the ninth, they do not have to play the bottom half of the inning
                break;
            }
            //same process to determine the outcome as above
            randNum = rand() % (16 - pTeam->getPlayers()->get(mHLineupPos)->getRating()) + pTeam->getPlayers()->get(mHLineupPos)->getRating();
            if(randNum >= 12){
                randNum = rand() % 11;
                if(randNum <= 6){
                    handleHit(pTeam, 1, mHLineupPos);
                }else if(randNum <= 8){
                    handleHit(pTeam,2, mHLineupPos);
                }else if(randNum == 9){
                    handleHit(pTeam,3,mHLineupPos);
                }else{
                    handleHit(pTeam,4,mHLineupPos);
                }
            }else{
                mNumOuts++;
                handleOut(pTeam, mHLineupPos);
            }
            mHLineupPos++;
            if(mHLineupPos == 9){
                mHLineupPos = 0;
            }
        }
    }
    //after the inning is over, all the players that were on base have to have their base values reset to 0 for the next inning
    for(int i = 0; i < 9; i++){
        pTeam->getPlayers()->get(i)->resetBase();
    }
    //after each inning, the outs must be reset as well
    mNumOuts = 0;
}

void Game::handleHit(Team* pTeam, const int HIT_VAL, const int POS){
    //the HIT_VAL passed in determines whether the hit is a single, double, triple, or homerun
    //for each possibility, a different cout statement is called to document the hit
    if(HIT_VAL == 1){
       cout << pTeam->getPlayers()->get(POS)->getName() << " singled" << endl;
    }else if(HIT_VAL == 2){
       cout << pTeam->getPlayers()->get(POS)->getName() << " doubled" << endl;
    }else if(HIT_VAL == 3){
        cout << pTeam->getPlayers()->get(POS)->getName() << " tripled" << endl;
    }else{
        cout << pTeam->getPlayers()->get(POS)->getName() << " hit a home run" << endl;
    }
    //this for loop will increment the base value for each player currently on base by the HIT_VAL
    //if a players base value is greater than 3, they score, and the score variable is incremented
    for(int i = 0; i < 9; i++){
        if(pTeam->getPlayers()->get(i)->getBase() != 0){
            pTeam->getPlayers()->get(i)->incrementBase(HIT_VAL);
        }
        if(pTeam->getPlayers()->get(i)->getBase() >= 4){
            pTeam->getPlayers()->get(i)->resetBase();
            if(mTop){
                mAScore++;
            }else{
                mHScore++;
                //if the home team takes the lead in the ninth inning,the game ends
                if(mInning >= mInningsToPlay && mHScore > mAScore){
                    mNumOuts = 3;
                    break;
                }
            }
            cout << pTeam->getPlayers()->get(i)->getName() << " scored!" << endl;
            printScore();
        }
    }
    //this if/else statement increments the base value of the player that actually got the hit
    if(mTop){
        if(HIT_VAL == 4){
            mAScore++;
            cout << pTeam->getPlayers()->get(mALineupPos)->getName() << " scored!" << endl;
            printScore();
        }else{
            pTeam->getPlayers()->get(mALineupPos)->incrementBase(HIT_VAL);
        }
    }else{
        if(HIT_VAL == 4){
            mHScore++;
            cout << pTeam->getPlayers()->get(mHLineupPos)->getName() << " scored!" << endl;
            printScore();
            if(mInning >= mInningsToPlay && mHScore > mAScore){
                mNumOuts = 3;
            }
        }else{
            pTeam->getPlayers()->get(mHLineupPos)->incrementBase(HIT_VAL);
        }
    }  
}

void Game::handleOut(Team* pTeam, const int POS){
    //if the player is out, a random number is generated to determine how they got out, which is then outputted to the console
    int random = rand() % 5;
    if(random == 0){
        cout << pTeam->getPlayers()->get(POS)->getName() << " struck out" << endl;
    }else if(random == 1){
        cout << pTeam->getPlayers()->get(POS)->getName() << " grounded out" << endl;
    }else if(random == 2){
        cout << pTeam->getPlayers()->get(POS)->getName() << " lined out" << endl;
    }else if(random == 3){
        cout << pTeam->getPlayers()->get(POS)->getName() << " popped out" << endl;
    }else{
        cout << pTeam->getPlayers()->get(POS)->getName() << " flew out" << endl;
    }
}

void Game::playExtras(Team* pHomeTeam, Team* pAwayTeam){
    //if extra innings are needed, additional innings are played until a winner is determined
    cout << "------------------------------" << endl;
    cout << "It is the top of the " << mInning << " inning!" << endl;
    mTop = true;
    playInning(pAwayTeam);
    cout << "------------------------------" << endl;
    cout << "It is the bottom of the " << mInning << " inning!" << endl;
    mTop = false;
    playInning(pHomeTeam);
    mInning++;
}

void Game::printWinner(Team* pHomeTeam, Team* pAwayTeam){
    //if the score is tied after 9 innings are played, the game goes into extra innings
    //this while loop handles an extra inning scenario
    while(mHScore == mAScore){
        playExtras(pHomeTeam,pAwayTeam);
    }
    //after the while loop is executed, the game is officially over with a valid winner
    //the winning team is then determined and printed to the console
    cout << "------------------------------" << endl;
    cout << "The final score is " << mAScore << " - " << mHScore << endl;
    if(mHScore > mAScore){
        cout << "The " << pHomeTeam->getName() << " win!" << endl;
    }else{
        cout << "The " << pAwayTeam->getName() << " win!" << endl;
    }
    cout << "------------------------------" << endl;
}

void Game::printScore() const{
    //prints the current score of the game
    cout << "The current score is " << mAScore << " - " << mHScore << endl;
}

void Game::setInningsToPlay(const int VAL){
    mInningsToPlay = VAL;
}
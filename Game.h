#ifndef GAME_H
#define GAME_H

#include "Team.h"

class Game{
public:
    Game();
    void playGame(Team* , Team*);
    void playInning(Team*);
    void handleHit(Team*, const int, const int);
    void handleOut(Team*, const int);
    void printWinner(Team*, Team*);
    void playExtras(Team*, Team*);
    void setInningsToPlay(const int);
    void printScore() const;
private:
    unsigned int mInning;
    unsigned int mHScore;
    unsigned int mAScore;
    unsigned int mHLineupPos;
    unsigned int mALineupPos;
    unsigned int mNumOuts;
    unsigned int mInningsToPlay;
    bool mTop;
};

#endif
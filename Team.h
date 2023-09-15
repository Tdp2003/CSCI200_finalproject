#ifndef TEAM_H
#define TEAM_H

#include "Array.hpp"
#include "Player.h"

class Team{
public:
    Team(const bool);
    string getName() const;
    List<Player*>* getPlayers() const;
    bool formTeam();
private:
    bool mHome;
    string mName;
    List<Player*>* mpPlayers;
};

#endif
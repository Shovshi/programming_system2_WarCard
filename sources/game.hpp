#pragma once
#include "player.hpp"
#include <string>
#include <cstdlib>
#include "card.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <stdexcept>

namespace ariel
{
    class Game
    {
    public:
        Player &p1;
        Player &p2;
        vector<Card> logCards;
        bool p1Win = false;
        bool p2Win = false;
        bool draw = false;
        Card faceDownCard1;
        Card faceDownCard2;
        vector<Card> drawCards;
        int numOfTurns;
        int drawsNum;

        Game(Player &play1, Player &play2);

        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
}

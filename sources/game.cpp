#include "game.hpp"
#include <cstdlib>
#include <iostream>

using namespace ariel;

Game::Game(Player &p1, Player &p2)
    : p1(p1), p2(p2)
{
    // Confirms that both of the players ready to play
    if (p1.isPlaying == true)
    {
        throw invalid_argument(p1.name + "invalid to play at this point");
    }

    if (p2.isPlaying == true)
    {
        throw invalid_argument(p2.name + "invalid to play a this point");
    }

    p1.isPlaying = true;
    p2.isPlaying = true;

    // Creats a deck of 52 cards for the game and push it by order to the vector
    vector<Card> deck;
    Card card;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            card.suit = Suit(suit);
            card.rank = Rank(rank);
            deck.push_back(card);
        };
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the deck
    std::shuffle(deck.begin(), deck.end(), g);

    // Divide the cards equally between the players
    size_t numCards = deck.size() / 2;
    for (size_t i = 0; i < numCards; i++)
    {
        p1.addCard(deck[i]);
        p2.addCard(deck[i + numCards]);
    }
}
void ariel::Game::playTurn()
{
    // std::cout << "p1 start with: " << p1.cards[0].getNumCard(p1.cards[0]) << std::endl;
    // std::cout << "p2 starts with: " << p2.cards[0].getNumCard(p2.cards[0]) << std::endl;
    if (&p1 == &p2)
    {
        throw invalid_argument("You can't play with the same player");
    }

    if (p1.stacksize() != 0)
    {
        numOfTurns++;
        Card firstP1 = p1.cards[0];
        p1.cards.erase(p1.cards.begin());
        Card firstP2 = p2.cards[0];
        p2.cards.erase(p2.cards.begin());

        logCards.push_back(firstP1);
        logCards.push_back(firstP2);
        p1.lastTurnCards.push_back(firstP1);
        p2.lastTurnCards.push_back(firstP2);

        // Draw
        while (firstP2.getNumCard() == firstP1.getNumCard())
        {
            draw = true;
            drawsNum++;
            p1Win = false;
            p2Win = false;
            if (p1.stacksize())
            {
                // Draw a face down card
                faceDownCard1 = p1.cards[0];
                p1.cards.erase(p1.cards.begin());
                faceDownCard2 = p2.cards[0];
                p2.cards.erase(p2.cards.begin());

                // Put the cards of the draw into a draw vector
                drawCards.push_back(firstP1);
                drawCards.push_back(firstP2);
                drawCards.push_back(faceDownCard1);
                drawCards.push_back(faceDownCard2);

                if (p1.stacksize())
                {
                    // Pull another regular card to continue the game
                    firstP1 = p1.cards[0];
                    p1.lastTurnCards.push_back(firstP1);
                    p1.cards.erase(p1.cards.begin());
                    firstP2 = p2.cards[0];
                    p2.lastTurnCards.push_back(firstP2);
                    p2.cards.erase(p2.cards.begin());
                }

                // std::cout<<"the regular card of p1 is: "<<firstP1.getNumCard(firstP1)<<std::endl;
                // std::cout<<"the regular card of p2 is: "<<firstP2.getNumCard(firstP2)<<std::endl;
            }
            else
            {
                while (drawCards.size())
                {
                    // Split all the draw cards equally between the players
                    p1.winsCards.push_back(drawCards[0]);
                    drawCards.erase(drawCards.begin());
                    p2.winsCards.push_back(drawCards[0]);
                    drawCards.erase(drawCards.begin());
                }
                draw = false;
            }
        }

        // If player1 has won
        if (firstP1.getNumCard() > firstP2.getNumCard() || (firstP1.getNumCard() == 2 && firstP2.getNumCard() == 14))
        {
            // If there was a draw before
            if (draw)
            {
                while (drawCards.size())
                {
                    p1.winsCards.push_back(drawCards[0]);
                    drawCards.erase(drawCards.begin());
                }
            }
            p1Win = true;
            p2Win = false;
            p1.winsNum++;
            draw = false;
            p1.winsCards.push_back(firstP1);
            p1.winsCards.push_back(firstP2);
        }

        // If player2 has won
        else if (firstP2.getNumCard() > firstP1.getNumCard() || (firstP1.getNumCard() == 14 && firstP2.getNumCard() == 2))
        {
            if (draw)
            {
                while (drawCards.size())
                {
                    p2.winsCards.push_back(drawCards[0]);
                    drawCards.erase(drawCards.begin());
                }
            }
            p1Win = false;
            p2Win = true;
            p2.winsNum++;
            draw = false;
            p2.winsCards.push_back(firstP1);
            p2.winsCards.push_back(firstP2);
        }
    }

    // Throw invalid argument because the cards are over
    else if (p1.cards.size() == 0)
    {
        throw invalid_argument("The cards are over");
    }

    // std::cout<<"last card of p1 is: "<<p1.cards[0].getNumCard(p1.cards[0])<<std::endl;
    // std::cout<<"last card of p2 is: "<<p2.cards[0].getNumCard(p2.cards[0])<<std::endl;
}

void ariel::Game::printLastTurn()
{
    for (size_t turns = 0; turns < p1.lastTurnCards.size(); turns++)
    {
        std::cout << p1.name << " played";
        p1.lastTurnCards[turns].printCard();
        std::cout << p2.name << " played";
        p2.lastTurnCards[turns].printCard();

        if (p1.lastTurnCards[turns].getNumCard() == p2.lastTurnCards[turns].getNumCard())
        {
            std::cout << "Draw." << std::endl;
        }

        else if (p1.lastTurnCards[turns].getNumCard() > p2.lastTurnCards[turns].getNumCard())
        {
            std::cout << p1.name << " wins." << std::endl;
        }

        else
        {
            std::cout << p2.name << " wins." << std::endl;
        }
    }
}

void ariel::Game::playAll()
{
    while (p1.cards.size())
    {
        playTurn();
    }
}
void ariel::Game::printWiner()
{
    std::cout << "......................." << std::endl;
    if (p1.winsCards.size() > p2.winsCards.size())
    {
        std::cout << p1.name << " won." << std::endl;
    }
    else if (p2.winsCards.size() > p1.winsCards.size())
    {
        std::cout << p2.name << " won." << std::endl;
    }
    else
    {
        std::cout << "Draw" << std::endl;
    }
}

void ariel::Game::printLog()
{
    std::cout << "......................." << std::endl;
    Card player1Card = logCards[0];
    Card player2Card = logCards[1];
    bool wasDraw = false;
    for (size_t turn = 0; turn < numOfTurns; turn++)
    {
        std::cout << p1.name << " played";
        player1Card.printCard();
        std::cout << p2.name << " played";
        player2Card.printCard();

        if (player1Card.getNumCard() > player2Card.getNumCard() || (player1Card.getNumCard() == 2 && player2Card.getNumCard() == 14))
        {
            wasDraw = false;
            std::cout << p1.name << " Won." << endl;
            logCards.erase(logCards.begin());
            logCards.erase(logCards.begin());
        }
        else if (player1Card.getNumCard() < player2Card.getNumCard() || (player1Card.getNumCard() == 14 && player2Card.getNumCard() == 2))
        {
            wasDraw = false;
            std::cout << p2.name << " Won." << endl;
            logCards.erase(logCards.begin());
            logCards.erase(logCards.begin());
        }

        player1Card = logCards[0];
        player2Card = logCards[1];

        while (logCards.size() && logCards[0].getNumCard() == logCards[1].getNumCard())
        {
            if (!wasDraw)
            {
                std::cout << p1.name << " played ";
                logCards[0].printCard();
                std::cout << p2.name << " played ";
                logCards[1].printCard();
            }

            std::cout << "Draw." << endl;
            logCards.erase(logCards.begin());
            logCards.erase(logCards.begin());

            if (wasDraw)
            {
                std::cout << p1.name << " played with ";
                logCards[0].printCard();
                std::cout << p2.name << " played with ";
                logCards[1].printCard();
            }

            wasDraw = true;
        }
    }
}

void ariel::Game::printStats()
{   
    std::cout << "......................." << std::endl;

    std::cout << "Stats of " << p1.name <<":"<< std::endl;
    std::cout<< "Win rate: "<<((double)p1.winsNum / (double)numOfTurns)*100 <<"%"<< std::endl;;
    std::cout<<"Cards won: "<< p1.winsCards.size()<<endl;

    std::cout<< "----"<< std::endl;

    std::cout << "Stats of " << p2.name <<":"<< std::endl;
    std::cout<< "Win rate: "<<((double)p2.winsNum / (double)numOfTurns)*100 <<"%"<< std::endl;;
    std::cout<<"Cards won: "<< p2.winsCards.size()<<endl;

    std::cout<<"----"<<std::endl;
    std::cout<<"Draw rate: "<<((double)drawsNum / (double)numOfTurns)*100 <<"%"<< std::endl;
    std::cout<<"Amount of draws: "<<drawsNum<<std::endl;

}

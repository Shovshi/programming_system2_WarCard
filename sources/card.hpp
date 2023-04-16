#pragma once

enum Suit {HEARTS, SPADES, CLUBS, DIAMONDS};
enum Rank {TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
  
class Card {
public:
  Rank rank;
  Suit suit;
  
  Card():rank(TWO), suit(HEARTS){};

  Card(Rank rank, Suit suit) : rank(rank), suit(suit) {
    rank = rank;
    suit = suit;
  }

  
  int getNumCard();
  
  void printCard();
};



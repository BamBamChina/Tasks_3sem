#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

enum class Suit { HEARTS, DIAMONDS, CLUBS, SPADES };
enum class Rank { 
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, 
    EIGHT, NINE, TEN, JACK, QUEEN, KING 
};

class Card {
private:
    Suit suit;
    Rank rank;
    bool isFaceUp;

public:
    Card(Suit s, Rank r);
    
    int getValue() const;
    std::string toString() const;
    void flip();
    bool isFacedUp() const;
    
    Suit getSuit() const { return suit; }
    Rank getRank() const { return rank; }
};

#endif

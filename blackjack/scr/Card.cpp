#include "Card.h"
#include <map>
#include <sstream>

Card::Card(Suit s, Rank r) : suit(s), rank(r), isFaceUp(true) {}

int Card::getValue() const {
    int value = static_cast<int>(rank);
    if (value > 10) value = 10;
    return value;
}

std::string Card::toString() const {
    if (!isFaceUp) return "[Hidden]";
    
    static const std::map<Suit, std::string> suitStrings = {
        {Suit::HEARTS, "♥"}, {Suit::DIAMONDS, "♦"},
        {Suit::CLUBS, "♣"}, {Suit::SPADES, "♠"}
    };
    
    static const std::map<Rank, std::string> rankStrings = {
        {Rank::ACE, "A"}, {Rank::TWO, "2"}, {Rank::THREE, "3"},
        {Rank::FOUR, "4"}, {Rank::FIVE, "5"}, {Rank::SIX, "6"},
        {Rank::SEVEN, "7"}, {Rank::EIGHT, "8"}, {Rank::NINE, "9"},
        {Rank::TEN, "10"}, {Rank::JACK, "J"}, {Rank::QUEEN, "Q"},
        {Rank::KING, "K"}
    };
    
    std::stringstream ss;
    ss << rankStrings.at(rank) << suitStrings.at(suit);
    return ss.str();
}

void Card::flip() {
    isFaceUp = !isFaceUp;
}

bool Card::isFacedUp() const {
    return isFaceUp;
}

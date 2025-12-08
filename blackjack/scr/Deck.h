#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>
#include <memory>

class Deck {
private:
    std::vector<std::shared_ptr<Card>> cards;
    std::mt19937 rng;
    
public:
    Deck();
    void shuffle();
    std::shared_ptr<Card> drawCard();
    void reset();
    int cardsRemaining() const;
};

#endif

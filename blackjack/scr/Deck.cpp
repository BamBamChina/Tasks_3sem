#include "Deck.h"
#include <algorithm>
#include <chrono>

Deck::Deck() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
    reset();
}

void Deck::reset() {
    cards.clear();
    for (int s = 0; s < 4; s++) {
        for (int r = 1; r <= 13; r++) {
            cards.push_back(std::make_shared<Card>(
                static_cast<Suit>(s), 
                static_cast<Rank>(r)
            ));
        }
    }
    shuffle();
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

std::shared_ptr<Card> Deck::drawCard() {
    if (cards.empty()) {
        reset();
        shuffle();
    }
    
    auto card = cards.back();
    cards.pop_back();
    return card;
}

int Deck::cardsRemaining() const {
    return cards.size();
}

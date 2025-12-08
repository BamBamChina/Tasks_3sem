#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
#include <memory>

class Hand {
protected:
    std::vector<std::shared_ptr<Card>> cards;
    
public:
    Hand();
    virtual ~Hand() = default;
    
    void addCard(std::shared_ptr<Card> card);
    void clear();
    int getValue() const;
    int getSoftValue() const; // Для вычисления вероятностей
    std::string toString(bool hideFirstCard = false) const;
    size_t getCardCount() const { return cards.size(); }
    bool isBusted() const;
    bool hasBlackjack() const;
    const std::vector<std::shared_ptr<Card>>& getCards() const { return cards; }
};

#endif

#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer : public Player {
private:
    std::shared_ptr<Card> hiddenCard;
    
public:
    Dealer();
    
    bool wantsHit() const override;
    void takeCard(std::shared_ptr<Card> card) override;
    void revealHiddenCard();
    std::shared_ptr<Card> getUpcard() const;
    int getUpcardValue() const;
    void newRound() override;
};

#endif

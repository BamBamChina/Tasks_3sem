#include "Dealer.h"

Dealer::Dealer() : Player("Дилер") {
    hiddenCard = nullptr;
}

bool Dealer::wantsHit() const {
    // Дилер берет карты по стандартным правилам
    int value = hand.getValue();
    return value < 17;
}

void Dealer::takeCard(std::shared_ptr<Card> card) {
    if (hand.getCardCount() == 1) {
        hiddenCard = card;
    }
    hand.addCard(card);
}

void Dealer::revealHiddenCard() {
    if (hiddenCard) {
        // Карта уже добавлена в руку, просто показываем
        hiddenCard = nullptr;
    }
}

std::shared_ptr<Card> Dealer::getUpcard() const {
    if (!hand.getCards().empty()) {
        return hand.getCards()[0];
    }
    return nullptr;
}

int Dealer::getUpcardValue() const {
    auto upcard = getUpcard();
    if (upcard) {
        return upcard->getValue();
    }
    return 0;
}

void Dealer::newRound() {
    Player::newRound();
    hiddenCard = nullptr;
}

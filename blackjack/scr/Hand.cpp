#include "Hand.h"
#include <sstream>
#include <algorithm>

Hand::Hand() {}

void Hand::addCard(std::shared_ptr<Card> card) {
    cards.push_back(card);
}

void Hand::clear() {
    cards.clear();
}

int Hand::getValue() const {
    int value = 0;
    int aces = 0;
    
    for (const auto& card : cards) {
        int cardValue = card->getValue();
        value += cardValue;
        if (cardValue == 1) aces++;
    }
    
    // Обработка тузов
    while (aces > 0 && value + 10 <= 21) {
        value += 10;
        aces--;
    }
    
    return value;
}

int Hand::getSoftValue() const {
    int value = 0;
    for (const auto& card : cards) {
        value += card->getValue();
    }
    return value;
}

bool Hand::isBusted() const {
    return getValue() > 21;
}

bool Hand::hasBlackjack() const {
    return cards.size() == 2 && getValue() == 21;
}

std::string Hand::toString(bool hideFirstCard) const {
    std::stringstream ss;
    ss << "Сумма: " << getValue() << " | Карты: ";
    
    for (size_t i = 0; i < cards.size(); i++) {
        if (hideFirstCard && i == 0) {
            ss << "[Hidden] ";
        } else {
            ss << cards[i]->toString() << " ";
        }
    }
    
    if (isBusted()) ss << "| Перебор!";
    else if (hasBlackjack()) ss << "| Blackjack!";
    
    return ss.str();
}

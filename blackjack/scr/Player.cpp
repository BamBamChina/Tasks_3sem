#include "Player.h"
#include <cmath>
#include <sstream>

Player::Player(const std::string& playerName) 
    : name(playerName), isActive(true), wins(0), gamesPlayed(0) {}

void Player::takeCard(std::shared_ptr<Card> card) {
    hand.addCard(card);
}

void Player::newRound() {
    hand.clear();
    isActive = true;
    gamesPlayed++;
}

void Player::endRound(bool won) {
    if (won) wins++;
}

double Player::getWinRate() const {
    if (gamesPlayed == 0) return 0.0;
    return static_cast<double>(wins) / gamesPlayed;
}

std::string Player::getStats() const {
    std::stringstream ss;
    ss << name << ": " << wins << "/" << gamesPlayed 
       << " побед (" << (getWinRate() * 100) << "%)";
    return ss.str();
}

double Player::calculateWinProbability(int dealerUpcard, int remainingCards) const {
    int playerValue = hand.getValue();
    
    if (playerValue > 21) return 0.0; // Уже проиграли
    if (playerValue == 21) return 0.95; // Почти гарантированная победа
    
    // Простая модель вероятности
    // Более точная модель потребовала бы подсчета оставшихся карт
    double baseProb = 0.5;
    
    // Корректировка на основе счета игрока
    if (playerValue >= 19) baseProb = 0.7;
    else if (playerValue >= 17) baseProb = 0.6;
    else if (playerValue <= 12) baseProb = 0.3;
    
    // Корректировка на основе карты дилера
    if (dealerUpcard >= 7) baseProb *= 0.8; // Сильная карта дилера
    else if (dealerUpcard <= 3) baseProb *= 1.2; // Слабая карта дилера
    
    return std::min(0.95, std::max(0.05, baseProb));
}

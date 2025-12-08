#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>
#include <memory>

class Player {
protected:
    std::string name;
    Hand hand;
    bool isActive;
    int wins;
    int gamesPlayed;
    
public:
    Player(const std::string& playerName);
    virtual ~Player() = default;
    
    virtual bool wantsHit() const = 0;
    virtual void takeCard(std::shared_ptr<Card> card);
    virtual void newRound();
    virtual void endRound(bool won);
    
    std::string getName() const { return name; }
    Hand& getHand() { return hand; }
    const Hand& getHand() const { return hand; }
    bool getIsActive() const { return isActive; }
    void setIsActive(bool active) { isActive = active; }
    
    double getWinRate() const;
    std::string getStats() const;
    
    // Вероятность выигрыша на основе текущей руки
    virtual double calculateWinProbability(int dealerUpcard, int remainingCards) const;
};

#endif

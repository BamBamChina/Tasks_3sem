#include <random>
#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>

class Base {
public:
    virtual unsigned roll() = 0;
    virtual ~Base() = default;
};

class Dice : public Base {
public:
    Dice(unsigned max, unsigned seed) 
        : max(max), dstr(1, max), reng(seed) {}
    
    unsigned roll() override {
        return dstr(reng);
    }
    
    unsigned getMax() const { return max; }

private:
    unsigned max;
    std::uniform_int_distribution<unsigned> dstr;
    std::default_random_engine reng;
};

class ThreeDicePool : public Base {
public:
    ThreeDicePool(unsigned max, unsigned seed1, unsigned seed2, unsigned seed3)
        : dice1(std::make_unique<Dice>(max, seed1)),
          dice2(std::make_unique<Dice>(max, seed2)),
          dice3(std::make_unique<Dice>(max, seed3)) {}

    unsigned roll() override {
        return dice1->roll() + dice2->roll() + dice3->roll();
    }

private:
    std::unique_ptr<Dice> dice1, dice2, dice3;
};

class PenaltyDice : public Base {   
public:
    PenaltyDice(Base& dice) : dice(dice) {}
    
    unsigned roll() override {   // Переопределение виртуальной функции roll() из базового класса
        unsigned roll1 = dice.roll();
        unsigned roll2 = dice.roll();
        return std::min(roll1, roll2);
    }

private:
    Base& dice;
};

class BonusDice : public Base {
public:
    BonusDice(Base& dice) : dice(dice) {}
    
    unsigned roll() override {
        unsigned roll1 = dice.roll();
        unsigned roll2 = dice.roll();
        return std::max(roll1, roll2);
    }

private:
    Base& dice;
};

double expected_value(Base& r, unsigned number_of_rolls = 1000) {
    unsigned long long accum = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        accum += r.roll();
    }
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}

double value_probability(unsigned value, Base& d, unsigned number_of_rolls = 10000) {
    unsigned count = 0;
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) { //Цикл по всем броскам
        if (d.roll() == value) {
            ++count;
        }
    }
    return static_cast<double>(count) / static_cast<double>(number_of_rolls);
}

void print_histogram(Base& d, unsigned min_value, unsigned max_value, 
                    unsigned number_of_rolls = 10000, const std::string& label = "") {
    std::cout << "Гистограмма " << label << ":\n";
    for (unsigned value = min_value; value <= max_value; ++value) {
        double prob = value_probability(value, d, number_of_rolls);
        std::cout << value << ": " << prob;
        
        // Визуализация гистограммы
        int bars = static_cast<int>(prob * 200); // Масштабируем для лучшей визуализации
        for (int i = 0; i < bars; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

int main() {
    // Тестирование для Dice [1,100]
    Dice d100(100, 42);
    PenaltyDice penalty_d100(d100);
    BonusDice bonus_d100(d100);
    
    std::cout << "=== ДЛЯ КУБИКА [1,100] ===\n";
    std::cout << "Обычный бросок - мат. ожидание: " << expected_value(d100, 10000) << std::endl;
    std::cout << "Штраф - мат. ожидание: " << expected_value(penalty_d100, 10000) << std::endl;
    std::cout << "Преимущество - мат. ожидание: " << expected_value(bonus_d100, 10000) << std::endl;
    
    // Построение гистограмм для Dice [1,100]
    print_histogram(d100, 1, 10, 10000, "обычный бросок [1,100] (первые 10 значений)");
    print_histogram(penalty_d100, 1, 10, 10000, "штраф [1,100] (первые 10 значений)");
    print_histogram(bonus_d100, 1, 10, 10000, "преимущество [1,100] (первые 10 значений)");
    
    // Тестирование для ThreeDicePool [1,6] × 3
    ThreeDicePool tdp(6, 1, 2, 3);
    PenaltyDice penalty_tdp(tdp);
    BonusDice bonus_tdp(tdp);
    
    std::cout << "=== ДЛЯ THREE DICE POOL [1,6] × 3 ===\n";
    std::cout << "Обычный бросок - мат. ожидание: " << expected_value(tdp, 10000) << std::endl;
    std::cout << "Штраф - мат. ожидание: " << expected_value(penalty_tdp, 10000) << std::endl;
    std::cout << "Преимущество - мат. ожидание: " << expected_value(bonus_tdp, 10000) << std::endl;
    
    // Построение гистограмм для ThreeDicePool (диапазон сумм от 3 до 18)
    print_histogram(tdp, 3, 12, 10000, "ThreeDicePool обычный (значения 3-12)");
    print_histogram(penalty_tdp, 3, 12, 10000, "ThreeDicePool штраф (значения 3-12)");
    print_histogram(bonus_tdp, 3, 12, 10000, "ThreeDicePool преимущество (значения 3-12)");

    return 0;
}

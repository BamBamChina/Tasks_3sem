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


class PenaltyDice : virtual public Base {   
public:
    PenaltyDice(Base& dice) : dice(dice) {}
    
    unsigned roll() override {
        unsigned roll1 = dice.roll();
        unsigned roll2 = dice.roll();
        return std::min(roll1, roll2);
    }

private:
    Base& dice;
};

class BonusDice : virtual public Base {
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

// === РЕШЕНИЕ ЗАДАНИЯ 3 ===

// Реализация с множественным наследованием
class DoubleDice : public PenaltyDice, public BonusDice {
public:
    DoubleDice(Dice& dice) 
        : Base(), PenaltyDice(dice), BonusDice(dice), dice(dice) {} //вызываем конструктор Base, тк наследование виртуаальное
    
    //указываем, какой метод roll использовать
    unsigned roll() override {
        return (PenaltyDice::roll() + BonusDice::roll()) / 2;
    }

private:
    Dice& dice;
};

// Реализация без множественного наследования
class DoubleDiceNoMI : public Base {
public:
    DoubleDiceNoMI(Dice& dice) : dice(dice) {}
    
    unsigned roll_penalty() {
        unsigned roll1 = dice.roll();
        unsigned roll2 = dice.roll();
        return std::min(roll1, roll2);
    }
    
    unsigned roll_bonus() {
        unsigned roll1 = dice.roll();
        unsigned roll2 = dice.roll();
        return std::max(roll1, roll2);
    }
    
    unsigned roll() override {
        return (roll_penalty() + roll_bonus()) / 2;
    }

private:
    Dice& dice;
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
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
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
        
        int bars = static_cast<int>(prob * 200);
        std::cout << " ";
        for (int i = 0; i < bars; ++i) {
            std::cout << "*";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void print_double_dice_stats(DoubleDice& dd, DoubleDiceNoMI& dd_no_mi, unsigned number_of_rolls = 10000) {
    std::cout << "=== СТАТИСТИКА DOUBLE DICE ===\n";
    
    // Тестирование через expected_value
    std::cout << "С множественным наследованием: " << expected_value(dd, number_of_rolls) << std::endl;
    std::cout << "Без множественного наследования: " << expected_value(dd_no_mi, number_of_rolls) << std::endl;
    
    // Дополнительная проверка - сравнение нескольких бросков
    std::cout << "\nПервые 10 бросков для сравнения:\n";
    std::cout << "С наследованием: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << dd.roll() << " ";
    }
    std::cout << "\nБез наследования: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << dd_no_mi.roll() << " ";
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

    // === ТЕСТИРОВАНИЕ ЗАДАНИЯ 3 ===
    std::cout << "\n" << std::string(50, '=') << "\n";
    std::cout << "ЗАДАНИЕ 3: DOUBLE DICE\n";
    std::cout << std::string(50, '=') << "\n";
    
    // Создание DoubleDice объектов
    DoubleDice double_dice(d100);
    DoubleDiceNoMI double_dice_no_mi(d100);
    
    // Статистика
    print_double_dice_stats(double_dice, double_dice_no_mi, 10000);
    
    // Гистограммы для DoubleDice
    std::cout << "\nГистограммы для DoubleDice [1,100]:\n";
    print_histogram(double_dice, 1, 20, 10000, "DoubleDice (с наследованием) первые 20 значений");
    print_histogram(double_dice_no_mi, 1, 20, 10000, "DoubleDice (без наследования) первые 20 значений");
    
    return 0;
}

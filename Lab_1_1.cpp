#include <random>
#include <memory>
#include <iostream>

class Base { //создаем базовый класс 
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

double expected_value(Base& r, unsigned number_of_rolls = 1000) {
    unsigned long long accum = 0; //считаем сумму всех бросков
    for (unsigned cnt = 0; cnt != number_of_rolls; ++cnt) {
        accum += r.roll();
    }
    return static_cast<double>(accum) / static_cast<double>(number_of_rolls);
}


int main() {
    Dice d(6, 42); // кубик от 1 до 6
    ThreeDicePool tdp(6, 1, 2, 3); // три кубика от 1 до 6

    std::cout << "Dice expected value: " << expected_value(d, 10000) << std::endl; //вычисляем мат ожидание для 10000 бросков
    std::cout << "ThreeDicePool expected value: " << expected_value(tdp, 10000) << std::endl;

    return 0;
}

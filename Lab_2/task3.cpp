#include <cassert>
#include <vector>
#include <memory>

//сетка размерности 1
template<typename T, size_t Dim>
class Grid;

//специализация для dim = 1
template<typename T>
class Grid<T, 1> {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<T> data;
    size_type size_;

public:
    //конструкторы
    Grid(T const& t) : size_(1) {
        data.push_back(t);
    }

    Grid(size_type size) : size_(size) {
        data.resize(size);
    }

    Grid(size_type size, T const& t) : size_(size) {
        data.resize(size, t);
    }

    //конструктор для инициализации списком размеров (для рекурсии)
    template<typename... Args>
    Grid(size_type first, Args... args) : size_(first) {
        data.resize(first, T(args...));
    }



    ~Grid() = default;
    Grid(Grid const&) = default;
    Grid(Grid&&) = default;
    Grid& operator=(Grid const&) = default;
    Grid& operator=(Grid&&) = default;

    //оператор доступа через круглые скобки
    T const& operator()(size_type idx) const {
        return data[idx];
    }

    T& operator()(size_type idx) {
        return data[idx];
    }

    //оператор индексирования - возвращает элемент (для Dim=1)
    T const& operator[](size_type idx) const {
        return data[idx];
    }

    T& operator[](size_type idx) {
        return data[idx];
    }

    //присваивание значения всем элементам
    Grid& operator=(T const& t) {
        for (auto& item : data) {
            item = t;
        }
        return *this;
    }

    size_type size() const { return size_; }
};

//сетка большей размерности
template<typename T, size_t Dim>
class Grid {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    std::vector<Grid<T, Dim - 1>> data;
    size_type size_;

public:
    //конструктор с одним параметром (неявное преобразование)
    Grid(T const& t) : size_(1) {
        data.emplace_back(t);
    }

    //конструктор с размерами и значением по умолчанию
    Grid(size_type size) : size_(size) {
        data.resize(size);
    }

    //конструктор с размерами и конкретным значением
    Grid(size_type size, T const& t) : size_(size) {
        data.resize(size, Grid<T, Dim - 1>(t));
    }

    //вариативный конструктор для произвольного количества размеров
    template<typename... Args>
    Grid(size_type first, Args... args) : size_(first) {
        data.resize(first, Grid<T, Dim - 1>(args...));
    }



    ~Grid() = default;
    Grid(Grid const&) = default;
    Grid(Grid&&) = default;
    Grid& operator=(Grid const&) = default;
    Grid& operator=(Grid&&) = default;

    //оператор доступа через круглые скобки
    template<typename... Indices>
    T const& operator()(size_type first, Indices... rest) const {
        return data[first](rest...);
    }

    template<typename... Indices>
    T& operator()(size_type first, Indices... rest) {
        return data[first](rest...);
    }

    //оператор индексирования - возвращает сетку меньшей размерности
    Grid<T, Dim - 1> const& operator[](size_type idx) const {
        return data[idx];
    }

    Grid<T, Dim - 1>& operator[](size_type idx) {
        return data[idx];
    }

    //присваивание значения всем элементам
    Grid& operator=(T const& t) {
        for (auto& item : data) {
            item = t;
        }
        return *this;
    }

    size_type size() const { return size_; }
};

//специализация для удобства: Grid<T> = Grid<T, 2> (двумерная сетка)
template<typename T>
using Grid2D = Grid<T, 2>;





int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));
    
    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));
    
    g2 = g3[1];
    assert(1.0f == g2(1, 1));

    return 0;
}

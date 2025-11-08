#include <cassert>

template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type y_size, x_size;

    //вспомогательный класс для реализации g[y][x]
    class RowProxy {
        T* row_start; //указатель на начало строки в массиве data
        size_type row_length; //длина сстроки
    public:
        RowProxy(T* start, size_type length) : row_start(start), row_length(length) {}
        
        T& operator[](size_type x_idx) {
            return row_start[x_idx];
        }
    };

    class ConstRowProxy {
        const T* row_start;
        size_type row_length;
    public:
        ConstRowProxy(const T* start, size_type length) : row_start(start), row_length(length) {}
        
        const T& operator[](size_type x_idx) const {
            return row_start[x_idx];
        }
    };

public:
    Grid(T const& t) : y_size(1), x_size(1) {
        data = new T[1]{t};
    }

    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size]();
    }

    Grid(size_type y_size, size_type x_size, T const& t) 
        : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }

    ~Grid() {
        delete[] data;
    }

    Grid(Grid const& other) 
        : y_size(other.y_size), x_size(other.x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = other.data[i];
        }
    }

    Grid(Grid&& other) noexcept 
        : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr;
        other.y_size = 0;
        other.x_size = 0;
    }

    Grid& operator=(Grid const& other) {
        if (this != &other) {
            delete[] data;
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size];
            for (size_type i = 0; i < y_size * x_size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    Grid& operator=(Grid&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr;
            other.y_size = 0;
            other.x_size = 0;
        }
        return *this;
    }

    //операторы доступа к элементам через круглые скобки
    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    //операторы индексирования через квадратные скобки 
    RowProxy operator[](size_type y_idx) {
        return RowProxy(data + y_idx * x_size, x_size); //вычисляем указатель на начало строки y_idx
    }
    
    ConstRowProxy operator[](size_type y_idx) const {
        return ConstRowProxy(data + y_idx * x_size, x_size);
    }



    
    Grid& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};





int main() {
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<float>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g(y_idx, x_idx));

    return 0;
}

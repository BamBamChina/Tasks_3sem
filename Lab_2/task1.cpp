template <typename T>
class Grid final {
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;
    size_type y_size, x_size;

public:
    // конструктор с одним параметром (неявное преобразование из T в Grid<T>)

    Grid(T const& t) : y_size(1), x_size(1) {
        data = new T[1]{t};
    }

    // конструктор с двумя параметрами

    Grid(size_type y_size, size_type x_size) : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size](); 
    }

    // конструктор с тремя параметрами 

    Grid(size_type y_size, size_type x_size, T const& t) 
        : y_size(y_size), x_size(x_size) {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = t;
        }
    }

    //правило пяти: если класс требует явного определения 
    //одного из следующих специальных методов, то, скорее всего, ему нужны все пять

    //деструктор
    ~Grid() {
        delete[] data;
    }

    //конструктор копирования
    Grid(Grid const& other) 
        : y_size(other.y_size), x_size(other.x_size) {
        data = new T[y_size * x_size]; //выделяем новую память
        for (size_type i = 0; i < y_size * x_size; ++i) {
            data[i] = other.data[i]; //копируем все элементы в новый массив
        }
    }

    //конструктор перемещения
    Grid(Grid&& other) noexcept //noexcept для оптимизации
        : data(other.data), y_size(other.y_size), x_size(other.x_size) {
        other.data = nullptr; //обнуляем исходный объект
        other.y_size = 0;
        other.x_size = 0;
    }

    //оператор присваивания копированием
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

    //оператор присваивания перемещением
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

    //операторы доступа к элементам
    T operator()(size_type y_idx, size_type x_idx) const {
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) {
        return data[y_idx * x_size + x_idx];
    }

    //присваивание всему Grid значения типа T
    Grid& operator=(T const& t) {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) {
            *it = t;
        }
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};

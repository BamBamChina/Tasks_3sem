#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <iomanip>

//классс исключений
class bad_from_string : public std::exception {
private:
    std::string message;

public:
    bad_from_string(const std::string& msg) : message(msg) {}
    
    // переопределение метода what()
    const char* what() const noexcept override {
        return message.c_str();
    }
};

//шаблонная функция для преобразования строки в тип T
template<class T>
T from_string(std::string const& s)
{
    std::istringstream iss(s);
    T result;
    
    //чтобы не пропускать пробелы
    iss >> std::noskipws >> result;
    
    // проверяем, было ли успешное преобразование и достигнут ли конец строки
    if (iss.fail() || !iss.eof()) {
        throw bad_from_string("Failed to convert string to required type");
    }
    
    return result;
}

// Специализация для std::string (просто возвращаем исходную строку)
template<>
std::string from_string<std::string>(std::string const& s)
{
    return s;
}

// Специализация для char
template<>
char from_string<char>(std::string const& s)
{
    if (s.length() != 1) {
        throw bad_from_string("String length must be exactly 1 for char conversion");
    }
    
    std::istringstream iss(s);
    char result;
    iss >> std::noskipws >> result;
    
    if (iss.fail()) {
        throw bad_from_string("Failed to convert string to char");
    }
    
    return result;
}

//пример использования
int main() {
    try {
        std::string s1("123");
        int a1 = from_string<int>(s1);
        std::cout << "a1 = " << a1 << std::endl; // a1 = 123
        
        double b1 = from_string<double>(s1);
        std::cout << "b1 = " << std::fixed << b1 << std::endl; // b1 = 123.0
        
        std::string c1 = from_string<std::string>(s1);
        std::cout << "c1 = " << std::quoted(c1) << std::endl; // c1 = "123"
        
        std::string s2("12.3");
        int a2 = from_string<int>(s2); // исключение
        std::cout << "a2 = " << a2 << std::endl;

        double b2 = from_string<double>(s2);
        std::cout << "b2 = " << std::fixed << b2 << std::endl; // b2 = 12.3
        
        std::string c2 = from_string<std::string>(s2);
        std::cout << "c2 = " << std::quoted(c2) << c2 << std::endl; // c2 = "12.3"
        
        // Тест с пробелами
        std::string s4(" 123");
        int a4 = from_string<int>(s4); // исключение из-за пробела
        std::cout << "a4 = " << a4 << std::endl;

        // Тест с char
        std::string s5("A");
        char ch = from_string<char>(s5);
        std::cout << "ch = " << ch << std::endl; // ch = A
    
    } catch (const bad_from_string& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    
    return 0;
}

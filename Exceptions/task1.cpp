#include <string>
#include <exception>
#include <iostream>

class MathException : public std::exception {
protected:
    std::string message;

public:
    MathException() : message("Mathematical error occurred") {}
    MathException(const std::string& msg) : message(msg) {}
    
    // Метод what() - возвращает строку ошибки
    virtual const char* what() const noexcept override {
        return message.c_str();
    }
    
    virtual ~MathException() = default;
};

// создаем класс исключений при делении на 0

class DivisionByZeroError : public MathException {
public:
    DivisionByZeroError() : MathException("Division by zero error") {}
    DivisionByZeroError(const std::string& msg) : MathException("Division by zero error: " + msg) {}
};

int divide(int x, int y) { //переписываем функциюб используя класс исключений
    if (y == 0) throw DivisionByZeroError();
    return x / y;
}

int main() {
    try {
        int result = divide(10, 0);
    } catch (const MathException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

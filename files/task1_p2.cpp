#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream in("input.txt");
    std::ofstream out("output.txt");

    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Ошибка открытия файлов\n";
        return 1;
    }

    std::string line;
    while (std::getline(in, line)) {
        out << line;
        if (!in.eof()) out << '\n'; // чтобы не добавлять лишний перевод строки в конце
    }

    in.close();
    out.close();
    return 0;
}

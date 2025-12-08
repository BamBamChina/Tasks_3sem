#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <string>

class TableReader {
private:
    std::vector<std::vector<int>> data;
    int rows;
    int cols;

public:
    TableReader(const std::string& filename) : rows(0), cols(0) {
        std::ifstream in(filename);
        if (!in.is_open()) {
            std::cerr << "Не удалось открыть файл " << filename << std::endl;
            return;
        }

        // Читаем N и M
        in >> rows >> cols;
        in.ignore(); 

        data.resize(rows, std::vector<int>(cols));

        std::string line;
        for (int i = 0; i < rows; ++i) {
            if (!std::getline(in, line)) {
                break;
            }
            std::stringstream ss(line);
            std::string cell;
            for (int j = 0; j < cols; ++j) {
                if (!std::getline(ss, cell, ',')) {
                    break;
                }
                data[i][j] = std::stoi(cell);
            }
        }
        in.close();
    }

    // вывод таблицы
    void printTable() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(10) << data[i][j];
                if (j != cols - 1) {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    TableReader table("input.txt");
    table.printTable();
    return 0;
}

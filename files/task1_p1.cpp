#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream input("input.txt");
    
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            std::cout << line << std::endl;
        }
    }
    
    return 0;
}

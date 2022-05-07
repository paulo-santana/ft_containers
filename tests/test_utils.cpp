#include <iostream>

void assertEquals(int lhs, int rhs, const std::string message) {
    if (lhs == rhs) {
        std::cout << "OK: " << message << std::endl;
    } else {
        std::cout << "WRONG: " << message
            << " (" << lhs << " == " << rhs << ")"
            << std::endl;
    }
}

void println(std::string str) {
    std::cout << str << std::endl;
}


#include <iostream>

template <typename T>
void assertEquals(T lhs, T rhs, const std::string message) {
    if (lhs == rhs) {
        std::cout << "OK: " << message << std::endl;
    } else {
        std::cout << "WRONG: " << message << std::endl;
    }
}

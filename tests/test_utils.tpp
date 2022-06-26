#include <iostream>

// classe que de propósito compara diferente do std::less
template<typename T>
class CustomComparator {

public:
    bool operator()(T lhs, T rhs) const {
        return lhs > rhs;
    }

};

template <typename T>
void assertEquals(T lhs, T rhs, const std::string message) {
    if (lhs == rhs) {
        std::cout << "OK: " << message << std::endl;
    } else {
        std::cout << "WRONG: " << message << std::endl;
    }
}

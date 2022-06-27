#include "Timer.hpp"
#include <iostream>

int main(void) {
    Timer timer;
    timer.reset();
    for (int i = 0; i < 4000000; i++) {
        std::cout << "adjfkadlsfjaklsdjfkas";
    }
    std::cout << "adjf" << std::endl;
    double time = timer.elapsed_seconds();
    std::cout << "elapsed time: " << time << std::endl;
}

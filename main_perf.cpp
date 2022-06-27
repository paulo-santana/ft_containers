#include "Timer.hpp"
#include "tests/test_utils.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

Timer timer;

static void print_times(long elements, double ft_seconds, double std_seconds) {
    std::cout << "ft::vector("<< elements << "): " << ft_seconds << std::endl;
    std::cout << "std::vector(" << elements << "): " << std_seconds << std::endl;

    if (ft_seconds > std_seconds) {
        double slower = ft_seconds / std_seconds;
        std::cout << "ft is ";
        std::string color = NORMAL;
        if (slower >= 20)
            color = RED;
        std::cout << color << slower << "x slower" << NORMAL << std::endl;
    } else {
        double faster = std_seconds / ft_seconds;
        std::cout << GREEN << "ft is " << faster << "x faster" << NORMAL << std::endl;
    }
}

static void test_vector_fill_constructor() {
    println("test vector fill constructor with ints");
    double ft_seconds, std_seconds;
    long n = 30000000;

    timer.reset();
    ft::vector<int> intvec(n);
    ft_seconds = timer.elapsed_seconds();

    timer.reset();
    std::vector<int> std_intvec(n);
    std_seconds = timer.elapsed_seconds();

    print_times(n, ft_seconds, std_seconds);

    println("test vector fill constructor with strings");
    timer.reset();
    ft::vector<std::string> string_vec(n, std::string("default"));
    ft_seconds = timer.elapsed_seconds();

    timer.reset();
    std::vector<std::string> std_string_vec(n, std::string("default"));
    std_seconds = timer.elapsed_seconds();

    print_times(n, ft_seconds, std_seconds);
}

static void test_vector_range_constructor() {
    println("test vector range constructor with ints");
    double ft_seconds, std_seconds;
    long n = 30000000;

    std::vector<int> basevec;
    for (int i = 0; i < n; i++) {
        basevec.push_back(n / 2 - i);
    }

    timer.reset();
    ft::vector<int> intvec(basevec.begin(), basevec.end());
    ft_seconds = timer.elapsed_seconds();

    timer.reset();
    std::vector<int> std_intvec(basevec.begin(), basevec.end());
    std_seconds = timer.elapsed_seconds();

    print_times(n, ft_seconds, std_seconds);

    println("test vector range constructor with strings");
    ft::vector<std::string> str_basevec(n, std::string("default"));

    timer.reset();
    ft::vector<std::string> string_vec(str_basevec.begin(), str_basevec.end());
    ft_seconds = timer.elapsed_seconds();

    timer.reset();
    std::vector<std::string> std_string_vec(str_basevec.begin(), str_basevec.end());
    std_seconds = timer.elapsed_seconds();

    print_times(n, ft_seconds, std_seconds);
}

static void test_vector_resize() {
    println("test vector resize with ints");
}

int main(void) {

    test_vector_fill_constructor();
    test_vector_range_constructor();
    test_vector_resize();
}

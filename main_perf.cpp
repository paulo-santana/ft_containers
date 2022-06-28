#include "Timer.hpp"
#include "tests/test_utils.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"

Timer timer;


#define TEST(FT_CONTAINER, STD_CONTAINER) { \
    timer.reset(); \
    {STD_CONTAINER} \
    std_seconds = timer.elapsed_seconds(); \
 \
    timer.reset(); \
    {FT_CONTAINER} \
    ft_seconds = timer.elapsed_seconds(); \
 \
    print_times(n, ft_seconds, std_seconds); \
}

static void print_times(long elements, double ft_seconds, double std_seconds) {
    std::cout << "ft working with "<< elements << " items: " << ft_seconds << std::endl;
    std::cout << "std working with " << elements << " items: " << std_seconds << std::endl;

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
    double ft_seconds, std_seconds;
    long n = 3000000;

    println("test vector fill constructor with ints");

    TEST(ft::vector<int> intvec(n);,
        std::vector<int> intvec(n);)

    println("test vector fill constructor with strings");
    TEST(ft::vector<std::string> string_vec(n, std::string("default"));,
        std::vector<std::string> std_string_vec(n, std::string("default"));)
}

static void test_vector_range_constructor() {
    double ft_seconds, std_seconds;
    long n = 3000000;

    ft::vector<int> basevec;
    for (int i = 0; i < n; i++) {
        basevec.push_back(n / 2 - i);
    }

    println("test vector range constructor with ints");
    TEST(ft::vector<int> intvec(basevec.begin(), basevec.end());,
        std::vector<int> std_intvec(basevec.begin(), basevec.end());)

    println("test vector range constructor with strings");
    ft::vector<std::string> str_basevec(n, std::string("default"));

    TEST(ft::vector<std::string> string_vec(str_basevec.begin(), str_basevec.end()); ,
        std::vector<std::string> std_string_vec(str_basevec.begin(), str_basevec.end());)
}

static void test_vector_resize() {
    println("test vector resize with ints");
    double ft_seconds, std_seconds;
    long n = 10000;

    TEST(
        for (int i = 1; i < n; i++) {
            ft::vector<int> ftvec;
            ftvec.resize(i, i);
        } , 
        for (int i = 1; i < n; i++) {
            std::vector<int> stdvec;
            stdvec.resize(i, i);
        }
    );
}

int main() {

    try {
        test_vector_fill_constructor();
        test_vector_range_constructor();
        test_vector_resize();
    } catch (std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }
}

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
    double ft_seconds, std_seconds; \
    timer.reset(); \
    std::cout << "running ft" << std::endl; \
    {FT_CONTAINER} \
    ft_seconds = timer.elapsed_seconds(); \
 \
    timer.reset(); \
    std::cout << "running std" << std::endl; \
    {STD_CONTAINER} \
    std_seconds = timer.elapsed_seconds(); \
 \
    print_times(ft_seconds, std_seconds); \
}

static void print_times(double ft_seconds, double std_seconds) {
    std::cout << "ft took " << ft_seconds << " seconds" << std::endl;
    std::cout << "std took " << std_seconds << " seconds" << std::endl;

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
    long n = 3000000;

    println("test vector fill constructor with ints");

    TEST(ft::vector<int> intvec(n);,
        std::vector<int> intvec(n);)

    println("test vector fill constructor with strings");
    TEST(ft::vector<std::string> string_vec(n, std::string("default"));,
        std::vector<std::string> std_string_vec(n, std::string("default"));)
}

static void test_vector_range_constructor() {
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
    long n = 20000;

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

    println("test vector resize with strings");
    TEST(
        for (int i = 1; i < n; i++) {
            ft::vector<std::string> ftvec;
            ftvec.resize(i, "opa");
        } , 
        for (int i = 1; i < n; i++) {
            std::vector<std::string> stdvec;
            stdvec.resize(i, "opa");
        }
    );
}

static void test_vector_insert() {
    long n = 40000;

    println("test vector insert ints at the end");
    TEST(
        ft::vector<int> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.end(), i);
        } , 
        std::vector<int> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.end(), i);
        }
    );

    println("test vector insert ints at the beginning");
    TEST(
        ft::vector<int> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin(), i);
        } , 
        std::vector<int> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin(), i);
        }
    );

    println("test vector insert ints in the middle");
    TEST(
        ft::vector<int> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin() + ftvec.size() / 2, i);
        } , 
        std::vector<int> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin() + stdvec.size() / 2, i);
        }
    );

    println("test vector insert strings in the middle");
    TEST(
        ft::vector<std::string> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin() + ftvec.size() / 2, "af");
        } , 
        std::vector<std::string> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin() + stdvec.size() / 2, "af");
        }
    );

    n = 5000;

    println("test vector inserting 100 strings 5000 times in the middle");
    TEST(
        ft::vector<std::string> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin() + ftvec.size() / 2, 100, "af");
        } , 
        std::vector<std::string> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin() + stdvec.size() / 2, 100, "af");
        }
    );

    println("test vector inserting 100 strings 5000 times in the beginning");
    TEST(
        ft::vector<std::string> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin(), 100, "af");
        } , 
        std::vector<std::string> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin(), 100, "af");
        }
    );

    ft::vector<std::string> base_vec(200, "nice");

    println("test vector range inserting 200 strings 5000 times in the beginning");
    TEST(
        ft::vector<std::string> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.insert(ftvec.begin(), base_vec.begin(), base_vec.end());
        } , 
        std::vector<std::string> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.insert(stdvec.begin(), base_vec.begin(), base_vec.end());
        }
    );
}

static void test_vector_assign() {
    println("test vector range assign with ints");

    long n = 2000000;

    ft::vector<int> base_intvec(1000, 9);

    TEST(
        ft::vector<int> ftvec;
        for (int i = 1; i < n; i++) {
            ftvec.assign(base_intvec.begin(), base_intvec.end());
        } , 
        std::vector<int> stdvec;
        for (int i = 1; i < n; i++) {
            stdvec.assign(base_intvec.begin(), base_intvec.end());
        }
    );

    ft::vector<std::string> base_vec(n, "nice");

    println("test vector range assign with strings");
    TEST(
        ft::vector<std::string> ftvec;
        ftvec.assign(base_vec.begin(), base_vec.end());
        , 
        std::vector<std::string> stdvec;
        stdvec.assign(base_vec.begin(), base_vec.end());
    );

    println("test vector fill assign with ints");
    TEST(
        ft::vector<int> ftvec;
        for (int i = 1; i < 40000; i++) {
            ftvec.assign(i, 42);
        } , 
        std::vector<int> stdvec;
        for (int i = 1; i < 40000; i++) {
            stdvec.assign(i, 42);
        }
    );

    println("test vector fill assign with strings");
    TEST(
        ft::vector<std::string> ftvec;
        ftvec.assign(n, "opa");
        , 
        std::vector<std::string> stdvec;
        stdvec.assign(n, "opa");
    );

}

static void test_vector_erase() {
    int n = 2000000;

    ft::vector<int> ftvec(n, 42);
    std::vector<int> stdvec(n, 42);

    println("test vector erase from begin with ints");
    TEST( ftvec.erase(ftvec.begin()); , 
        stdvec.erase(stdvec.begin());
    );

    ft::vector<std::string> ftstrvec(n, "opa");
    std::vector<std::string> stdstrvec(n, "opa");

    println("test vector erase from begin with strings");
    TEST( ftstrvec.erase(ftstrvec.begin()); , 
        stdstrvec.erase(stdstrvec.begin());
    );

    println("test vector erase range from begin to middle with ints");
    TEST( ftvec.erase(ftvec.begin(), ftvec.end() - ftvec.size() / 2); , 
        stdvec.erase(stdvec.begin(), stdvec.end() - stdvec.size() / 2);
    );

    println("test vector erase from begin with string");
    TEST(ftstrvec.erase(ftstrvec.begin(), ftstrvec.end() - ftstrvec.size() / 2); , 
        stdstrvec.erase(stdstrvec.begin(), stdstrvec.end() - stdstrvec.size() / 2);
    );
}

static void test_vector_clear() {
    println("test vector clear with ints");
    long n = 20000000;

    ft::vector<int> ftintvec(n, 42);
    std::vector<int> stdintvec(n, 42);

    TEST(
        ftintvec.clear();,
        stdintvec.clear();
    );

}

int main() {

    try {
        test_vector_clear();
        return 0;
        test_vector_fill_constructor();
        test_vector_range_constructor();
        test_vector_resize();
        test_vector_insert();
        test_vector_assign();
        test_vector_erase();
    } catch (std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }
}

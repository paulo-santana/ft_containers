#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <string>

template <typename T>
void assertEquals(T lhs, T rhs, const std::string message);

void assertEquals(int lhs, int rhs, const std::string message);

void println(std::string str);

#include "./test_utils.tpp"

#endif // !TEST_UTILS_H

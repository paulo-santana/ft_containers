#pragma once
#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template<typename T1, typename T2>
class pair {
public:
    typedef T1 first_type;
    typedef T2 second_type;

    T1 first;
    T2 second;

    // default constructor
    pair(): first(), second() {}

    template<typename U1, typename U2>
    pair(pair<U1, U2>& other): first(other.first), second(other.second) { }

    pair(const first_type& key, const second_type& value): first(key), second(value) { }
};

template<typename T1, typename T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<typename T1, typename T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs == rhs);
}

template<typename T1, typename T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<typename T1, typename T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs <= rhs);
}

template<typename T1, typename T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(rhs < lhs);
}

template<typename T1, typename T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return !(lhs < rhs);
}

template<typename T1, typename T2>
pair<T1, T2> make_pair(T1 x, T2 y) {
    return pair<T1, T2>(x, y);
}

}

#endif // !PAIR_HPP

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

}

#endif // !PAIR_HPP

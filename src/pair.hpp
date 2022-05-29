#pragma once
#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {

template<typename T1, typename T2>
class pair {
public:
    T1 first;
    T2 second;

    // default constructor
    pair(): first(), second() {}

    // template<typename U1, typename U2>
    // pair(pair<U1, U2>& other): first(other.first), second(other.second) { }

};

}

#endif // !PAIR_HPP

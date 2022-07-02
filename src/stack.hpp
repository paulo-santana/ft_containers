#pragma once
#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft {

template<typename T, typename Container = ft::vector<T> >
class stack {

public:
    typedef Container                       container_type;
    typedef typename Container::size_type   size_type;
    typedef typename Container::value_type  value_type;

    explicit stack(const container_type& cont = container_type()): c(cont) { }

    size_type size() const {
        return this->c.size();
    }

    bool empty() const {
        return this->c.empty();
    }

    value_type& top() {
        return this->c.back();
    }

    const value_type& top() const {
        return this->c.back();
    }

    void push(const value_type& item) {
        this->c.push_back(item);
    }

    void pop() {
        this->c.pop_back();
    }

    friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c == rhs.c;
    }

    friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c != rhs.c;
    }

    friend bool operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c < rhs.c;
    }

    friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c > rhs.c;
    }

    friend bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c <= rhs.c;
    }

    friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.c >= rhs.c;
    }

protected:
    container_type c;
};

}

#endif // !STACK_HPP

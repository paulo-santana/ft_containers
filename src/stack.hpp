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

    explicit stack(const container_type& cont = container_type()): container(cont) { }

    size_type size() const {
        return this->container.size();
    }

    bool empty() const {
        return this->container.empty();
    }

    value_type& top() {
        return this->container.back();
    }

    const value_type& top() const {
        return this->container.back();
    }

    void push(const value_type& item) {
        this->container.push_back(item);
    }

    void pop() {
        this->container.pop_back();
    }

    friend bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
        return lhs.container == rhs.container;
    }

private:
    container_type container;
};

}

#endif // !STACK_HPP

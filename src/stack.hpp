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

    explicit stack(const container_type& cont = container_type()): container(cont) { }

    size_type size() const {
        return this->container.size();
    }

private:
    container_type container;
};

}

#endif // !STACK_HPP

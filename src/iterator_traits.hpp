#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft {

template<typename _Iter>
class iterator_traits {
public:
    typedef typename _Iter::iterator_category   iterator_category;
    typedef typename _Iter::value_type          value_type;
    typedef typename _Iter::difference_type     difference_type;
    typedef typename _Iter::pointer             pointer;
    typedef typename _Iter::reference           reference;
};

template<typename T>
class iterator_traits<T*> {
public:
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
};

template<typename T>
class iterator_traits<const T*> {
public:
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef std::ptrdiff_t                      difference_type;
    typedef const T*                            pointer;
    typedef const T&                            reference;
};

}

#endif // !ITERATOR_TRAITS_HPP

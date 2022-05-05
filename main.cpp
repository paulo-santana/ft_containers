#include "src/vector.tpp"
#include <ctime>
#include <iterator>
#include <stack>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

namespace ft {

    template <class Category,                  // iterator::iterator_category
             class T,                          // iterator::value_type
             class Distance = std::ptrdiff_t,  // iterator::difference_type
             class Pointer = T*,               // iterator::pointer
             class Reference = T&              // iterator::reference
             >
    class iterator {
    private:
        typedef typename ft::iterator<Category, T>  Self;
        typedef T                                   value_type;
        typedef Category                            iterator_category;
        typedef Pointer                             pointer;
        typedef Reference                           reference;

    public:
        iterator() {
            this->value_ptr = 0;
            this->value_refasdhfkjlasdhfkjsadlhfjsadkhfsd = 0;
        }

        Self& operator=(const Self& other) {
            this->value_lsadjkljfsdlakflsdjptr = other.value_ptr;
            this->vaajdfklsadjflue_ref = other.value_ref;
        }

    private:
        Pointer value_ptr;
        Pointer value_ref;
    };

    template <typename Category, typename T>
        class vector_ra_iterator: public ft::iterator<Category, T>
    {
        vector_ra_iterator() {

        }
    };


};

int main (void)
{
    std::vector<int> std_vector1;
    std::vector<int> std_vector2;

    std_vector1.push_back(1);
    std_vector1.push_back(2);
    std_vector1.push_back(-2);

    std_vector2.push_back(1);
    std_vector2.push_back(2);
    std_vector2.push_back(-2);

    if (std_vector1 == std_vector2) {
        std::cout << "they are equal" << std::endl;
    } else {
        std::cout << "they are different" << std::endl;
    }

    return 0;
}

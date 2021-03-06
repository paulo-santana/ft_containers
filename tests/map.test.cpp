#include "test_utils.hpp"
#include <map>
#include <ostream>
#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <sstream>
#include <utility>
#include <typeinfo>

#if REAL_STD
    namespace ft = std;

#else

#include "map.hpp"
#include "vector.hpp"
#include "pair.hpp"

#endif

template<typename T, typename U>
static std::ostream& operator<<(std::ostream& out, const ft::pair<T, U>& p) {
    out << "  pair[" << p.first << ", " << p.second << "]";
    return out;
}


template<typename T, typename U, typename V>
std::ostream& operator<<(std::ostream& out, ft::map<T, U, V>& map) {
    typename ft::map<T, U, V>::iterator it = map.begin();
    while (it != map.end()) {
        out << *it << std::endl;
        ++it;
    }
    return out;
}

static void test_empty_constructor() {
    println("test map default constructor");

    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;
    std::cout << "int_map.size() - " << int_map.size();
    std::cout << "string_map.size() - " << string_map.size();

    ft::map<int, int> int_map2((std::less<int>()));

    ft::map<std::string, int> string_map2((std::less<std::string>()), std::allocator<ft::pair<std::string, int> >());

    std::cout << "int_map.size() - " << int_map2.size();
    std::cout << "string_map.size() - " << string_map2.size();
    std::cout << "at least it compiles" << std::endl;
}

static void test_range_constructor() {
    println("test map range constructor");

    ft::vector<ft::pair<int, int> > int_vec;

    for (int i = 0; i < 20; i++) {
        int_vec.push_back(ft::make_pair(20 - i, i));
    }

    ft::map<int, int> int_map(int_vec.begin(), int_vec.end());
    std::cout << "map:\n" << int_map << std::endl;
    std::cout << "map size: " << int_map.size() << std::endl;
}

static void test_copy_constructor() {
    println("test map copy constructor");

    ft::map<std::string, std::string> strmap;

    strmap.insert(ft::make_pair("c", "carac"));
    strmap.insert(ft::make_pair("b", "banab"));
    strmap.insert(ft::make_pair("a", "arara"));
    strmap.insert(ft::make_pair("d", "debed"));

    ft::map<std::string, std::string> copy_map(strmap);
    std::cout << "copy map:\n" << copy_map << std::endl;
}

static void test_assignment_operator() {
    println("test map assignment operator");

    ft::map<std::string, int> empty_map;
    ft::map<std::string, int, CustomComparator<const std::string> > strint_map;

    strint_map.insert(ft::make_pair("mathematics", 92));
    strint_map.insert(ft::make_pair("languages", 32));
    strint_map.insert(ft::make_pair("physics", 89));
    strint_map.insert(ft::make_pair("logic", 90));
    strint_map.insert(ft::make_pair("history", 40));

    ft::map<std::string, int, CustomComparator<const std::string> > map_copy;
    ft::map<std::string, int> empty_copy;
    map_copy = strint_map;
    empty_copy = empty_map;

    std::cout << "the empty copy:\n" << empty_copy << std::endl;
    std::cout << "the copy:\n" << map_copy << std::endl;
    std::cout << "the copy size:\n" << map_copy.size() << std::endl;
}

static void test_begin() {
    println("test map begin");

    ft::map<int, int> map;
    for (int i = 1; i < 30; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    std::cout << "map:\n" << map << std::endl;
    std::cout << "begin: " << *map.begin() << std::endl;
    std::cout << "insert pair[12, 12]" << std::endl;
    map.insert(ft::make_pair(12, 12));
    std::cout << "new begin: " << *map.begin() << std::endl;
    const ft::map<int, int> const_map = map;
    ft::map<int, int>::const_iterator const_begin = const_map.begin();

    std::cout << "const begin: " << *const_begin << std::endl;
}

static void test_end() {
    println("test map end");

    ft::map<int, int> map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int>::const_iterator iter = map.begin();
    ft::map<int, int>::const_iterator end = map.end();
    // the loop stops when it reaches the end
    for (; iter != end; ++iter) {
        std::cout << "item with key " << iter->first << ": " << iter->second << std::endl;
    }
}

static void test_rbegin() {
    println("test map rbegin");

    ft::map<int, int> map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int>::reverse_iterator riter = map.rbegin();

    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++riter) {
        std::cout << "item with key " << riter->first << ": " << riter->second << std::endl;
    }

    ft::map<int, int>::const_reverse_iterator criter = map.rbegin();

    std::cout << "test the const_reverse_iterator" << std::endl;
    for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++criter) {
        std::cout << "item with key " << criter->first << ": " << criter->second << std::endl;
    }

}

static void test_rend() {
    println("test map rend");

    ft::map<int, int, CustomComparator<int> > map;
    for (int i = 1; i < 10; i++) {
        map.insert(ft::make_pair(1000 / i, 12 * i));
    }

    ft::map<int, int, CustomComparator<int> >::reverse_iterator rend = map.rend();

    for (; rend != map.rbegin(); --rend) {
        std::cout << "item with key " << rend->first << ": " << rend->second << std::endl;
    }

    std::cout << "test the const_reverse_iterator" << std::endl;
    ft::map<int, int, CustomComparator<int> >::const_reverse_iterator crend = map.rend();

    for (; crend != map.rbegin(); --crend) {
        std::cout << "item with key " << crend->first << ": " << crend->second << std::endl;
    }
}

// shoudn't compile
// static void test_reverse_iterator_quirks() {
//     println("test reverse iterator quirks");
//
//     ft::map<int, int> map;
//     for (int i = 1; i < 10; i++) {
//         map.insert(ft::make_pair(1000 / i, 12 * i));
//     }
//
//     ft::map<int, int>::reverse_iterator riter = map.rbegin();
//
//     for (ft::map<int, int>::size_type i = 0; i < map.size() ; ++i, ++riter) {
//         std::cout << "item with key " << riter->first << ": " << riter->second << std::endl;
//     }
//
//     if (riter < map.rend()) {
//         std::cout << "this shoudn't be possible" << std::endl;
//     }
// }

static void test_empty() {
    println("test map.empty()");

    ft::map<int, int> empty_map;
    std::cout << "map empty: " << empty_map.empty() << std::endl;
    empty_map.insert(ft::make_pair(1, 3));
    std::cout << "empty after inserting?: " << empty_map.empty() << std::endl;
}

static void test_size() {
    println("test map size");
    ft::map<int, int> int_map;
    ft::map<std::string, int> string_map;

    std::cout << "int_map size: " << int_map.size() << std::endl;
    std::cout << "string_map size: " << string_map.size() << std::endl;
}

static void test_max_size() {
    println("test map max_size");

    ft::map<int, int> int_map;
    ft::map<std::string, std::string> string_map;

    if (int_map.max_size() == 0) {
        std::cout << "there's something wrong with the size" << std::endl;
    } else {
        std::cout << "at least size is not 0" << std::endl;
    }
}

static void test_access_operator() {
    println("test map operator[]");

    ft::map<std::string, int> int_map;
    int_map["physics"] = 90;
    int_map["mathematics"] = 94;
    int_map["logic"] = 89;
    int_map["history"] = 44;

    std::cout << "The map:\n" << int_map << std::endl;

    std::cout << "the 'logic' value: " << int_map["logic"] << std::endl;;

    std::cout << "filling a map with ints" << std::endl;;
    ft::map<int, int> ft_basemap;
    for (int i = 0; i < 20; i++) {
        ft_basemap[i] = i * i;
    }

    for (int i = 0; i < 20; i++) {
        ft_basemap[i] = ft_basemap[i + 1];
    };

    std::cout << "the resulting map" << int_map["logic"] << std::endl;;
}

static void test_access_operator_cplusplus() {

  ft::map<char,std::string, CustomComparator<char> > mymap;

  mymap['a']="an element";
  mymap['b']="another element";
  mymap['c']=mymap['b'];

  std::cout << "mymap['a'] is " << mymap['a'] << '\n';
  std::cout << "mymap['b'] is " << mymap['b'] << '\n';
  std::cout << "mymap['c'] is " << mymap['c'] << '\n';
  std::cout << "mymap['d'] is " << mymap['d'] << '\n';

  std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}

static void test_insert() {
    println("test map insert");

    println("insert a pair on an empty map");
    ft::map<std::string, std::string, CustomComparator<std::string> > strmap;
    strmap.insert(ft::make_pair("a", "arara"));
    std::cout << "map:\n" << strmap;

    println("insert a pair on a map with one element");
    strmap.insert(ft::make_pair("b", "brara"));
    std::cout << "map:\n" << strmap;

    println("test the return value of the insertion");
    ft::pair<ft::map<std::string, std::string>::iterator, bool> result;
    result = strmap.insert(ft::make_pair("c", "crcrc"));
    std::cout << "result->first: " << *result.first
        << "\nresult->second: " << result.second << std::endl;

    println("insert an item with an already existing key");
    result = strmap.insert(ft::make_pair("b", "dudududu"));
    std::cout << "result->first: " << *result.first
        << "\nresult->second: " << result.second << std::endl;

}

static void test_insert_with_hint() {
    println("test map insert with hint");

    println("insert a pair on an empty map with begin() as a hint");
    ft::map<std::string, std::string> strmap;
    strmap.insert(strmap.begin(), ft::make_pair("a", "arara"));
    std::cout << "map:\n" << strmap;

    println("insert another pair on a map with 1 element with begin() as a hint");
    strmap.insert(strmap.begin(), ft::make_pair("b", "brara"));
    std::cout << "map:\n" << strmap;

    {
        ft::map<int, int> intmap;
        println("fill a map with growing values using begin() as a hint");
        for (int i = 0; i < 20; i++) {
            intmap.insert(intmap.begin(), ft::make_pair(i, i * i));
        }
        std::cout << "map:\n" << intmap;
    }
    {
        ft::map<int, int> intmap;
        println("fill a map with growing values using end() as a hint");
        for (int i = 0; i < 20; i++) {
            intmap.insert(intmap.end(), ft::make_pair(i, i * i));
        }
        std::cout << "map:\n" << intmap;
    }
    {
        ft::map<int, int> intmap;
        println("fill a map with growing values using the last inserted element as a hint");
        ft::map<int, int>::iterator result = intmap.insert(intmap.begin(), ft::make_pair(0, 0));
        for (int i = 0; i < 20; i++) {
            result = intmap.insert(result, ft::make_pair(i, i * i));
        }
        std::cout << "map:\n" << intmap;
    }
    {
        ft::map<int, int, CustomComparator<int> > intmap;
        println("fill a map with diminishing values using the last inserted element as a hint and a custom comparator");
        ft::map<int, int>::iterator result = intmap.insert(intmap.begin(), ft::make_pair(0, 0));
        for (int i = 0; i < 20; i++) {
            result = intmap.insert(result, ft::make_pair(i, i * i));
        }
        std::cout << "map:\n" << intmap;
    }

    println("insert a pair using various hints");
    for (int hint_key = 1; hint_key < 14; hint_key += 2) {
        for (int i = 0; i < 15; i += 2) {
            ft::map<int, int> intmap;
            intmap.insert(ft::make_pair(7, 0));
            intmap.insert(ft::make_pair(3, 0));
            intmap.insert(ft::make_pair(11, 0));
            intmap.insert(ft::make_pair(1, 0));
            intmap.insert(ft::make_pair(5, 0));
            intmap.insert(ft::make_pair(9, 0));
            intmap.insert(ft::make_pair(13, 0));

            ft::map<int, int>::iterator hint = intmap.find(hint_key);
            std::cout << "insert " << i << " with " << hint_key << " as hint" << std::endl;
            intmap.insert(hint, ft::make_pair(i, 1));
            std::cout << "map:\n" << intmap << std::endl;
        }
    }
}

static void test_insert_range() {
    println("test map range insert");

    ft::vector<ft::pair<int, int> > intvec;
    for (int i = 0; i < 15; i++) {
        intvec.push_back(ft::make_pair(i * i - 1, i * i * 2));
    }

    println("insert in an empty map");
    {
        ft::map<int, int> intmap;
        intmap.insert(intvec.begin(), intvec.end());
        std::cout << "map size: " << intmap.size() << std::endl;
        std::cout << "map:\n" << intmap << std::endl;
    }
}

// TODO: this is linear, make it work in constant time
static void test_erase() {
    println("test map erase");

    ft::map<int, int> intmap;
    for (int i = 0; i < 15; i++) {
        intmap[i * i - 1] =  i * i * 2;
    }

    std::cout << "initial map:\n" << intmap << std::endl;
    intmap.erase(intmap.begin());
    std::cout << "delete begin():\n" << intmap << std::endl;
    intmap.erase(intmap.begin());
    std::cout << "delete begin():\n" << intmap << std::endl;
    intmap.erase(intmap.find(99));
    std::cout << "delete 99:\n" << intmap << std::endl;
    std::cout << "delete everything" << std::endl;
    while (intmap.size() > 0)
        intmap.erase(--intmap.end());
    std::cout << "map: " << intmap << std::endl;

}

static void test_erase_key() {
    println("test map delete by key");

    ft::map<int, int> intmap;
    for (int i = 0; i < 15; i++) {
        intmap[i * i - 1] =  i * i * 2;
    }

    std::cout << "initial map:\n" << intmap << std::endl;
    ft::map<int, int>::size_type result = intmap.erase(-1);
    std::cout << "delete -1:\n" << intmap << std::endl;
    std::cout << "result: " << result << std::endl;
    result = intmap.erase(0);
    std::cout << "delete 0:\n" << intmap << std::endl;
    std::cout << "result: " << result << std::endl;
    result = intmap.erase(99);
    std::cout << "delete 99:\n" << intmap << std::endl;
    std::cout << "delete everything" << std::endl;
    while (intmap.size() > 0)
        intmap.erase(--intmap.end());
    std::cout << "map: " << intmap << std::endl;
}

static void test_erase_range() {
    println("test map erase range");

    ft::map<int, int> intmap;

    intmap[-1] = 0;
    intmap[0] = 2;
    intmap[3] = 8;
    intmap[8] = 18;
    intmap[15] = 32;
    intmap[24] = 50;
    intmap[35] = 72;
    intmap[48] = 98;
    intmap[63] = 128;
    intmap[80] = 162;
    intmap[99] = 200;
    intmap[120] = 242;
    intmap[143] = 288;
    intmap[168] = 338;
    intmap[195] = 392;


    std::cout << "initial map:\n" << intmap << std::endl;
    // prettyPrint(intmap.get_tree());

    ft::map<int, int>::iterator first = intmap.begin();
    ft::map<int, int>::iterator last = intmap.begin();
    for (int i = 0; i < 5; ++i, ++first, ++last, ++last);

    std::cout << "erase 5 nodes in the middle" << std::endl;
    intmap.erase(first, last);

    std::cout << "map:\n" << intmap << std::endl;

    std::cout << "erase begin to end" << std::endl;
    intmap.erase(intmap.begin(), intmap.end());

    std::cout << "map:\n" << intmap << std::endl;
}

static void test_erase_range_custom_comparator() {
    println("test map erase range");

    ft::map<int, int, CustomComparator<int> > intmap;

    intmap[-1] = 0;
    intmap[0] = 2;
    intmap[3] = 8;
    intmap[8] = 18;
    intmap[15] = 32;
    intmap[24] = 50;
    intmap[35] = 72;
    intmap[48] = 98;
    intmap[63] = 128;
    intmap[80] = 162;
    intmap[99] = 200;
    intmap[120] = 242;
    intmap[143] = 288;
    intmap[168] = 338;
    intmap[195] = 392;


    std::cout << "initial map:\n" << intmap << std::endl;
    // prettyPrint(intmap.get_tree());

    ft::map<int, int, CustomComparator<int> >::iterator first = intmap.begin();
    ft::map<int, int, CustomComparator<int> >::iterator last = intmap.begin();
    for (int i = 0; i < 5; ++i, ++first, ++last, ++last);

    std::cout << "erase 5 nodes in the middle" << std::endl;
    intmap.erase(first, last);

    std::cout << "map:\n" << intmap << std::endl;

    std::cout << "erase begin to end" << std::endl;
    intmap.erase(intmap.begin(), intmap.end());

    std::cout << "map:\n" << intmap << std::endl;
}

static void test_erase_cplusplus()
{
  ft::map<char,int> mymap;
  ft::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator

  mymap.erase ('c');                  // erasing by key

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

static void test_swap() {
    println("test map swap");

    ft::map<int, int> mymap;
    ft::map<int, int> othermap;

    mymap[1] = 3;
    mymap[2] = 6;
    mymap[3] = 9;
    mymap[4] = 12;

    othermap[5] = 25;
    othermap[6] = 36;
    othermap[7] = 49;

    mymap.swap(othermap);


    std::cout << "mymap:\n" << mymap << std::endl;
    std::cout << "othermap:\n" << othermap << std::endl;
}

static void test_clear() {
    println("test map clear");

    ft::map<int, int> intmap;
    intmap[42] = 32;
    intmap[12] = 122;
    intmap[82] = 822;

    std::cout << "map before clear:\n" << intmap << std::endl;
    intmap.clear();
    std::cout << "map after clear:\n" << intmap << std::endl;
    std::cout << "clearing an empty map" << std::endl;
    ft::map<int, int> empty;
    empty.clear();
    std::cout << "empty map after clear:\n" << empty << std::endl;
}

static void test_key_comp() {
    println("test map key_comp()");

    ft::map<int, int> intmap;
    std::cout << "the default Comparator of a map is std::less: ";

    std::cout << (typeid(intmap.key_comp()).name()) << std::endl;

    println("a map can be assigned a comparator");

    ft::map<std::string, std::string, CustomComparator<const std::string> > custom_map;
    custom_map["aaa"] = "first";
    custom_map["bbb"] = "middle";
    custom_map["ccc"] = "last";

    std::cout << "customly comparated map:" << std::endl;

    ft::map<std::string, std::string, CustomComparator<const std::string> >::iterator iter = custom_map.begin();
    for (; iter != custom_map.end(); ++iter) {
        std::cout << *iter << std::endl;
    }
}

static void test_value_comp() {
    println("test map value_comp()");

    ft::map<int, int> intmap;

    intmap[3] = 42;
    intmap[2] = 32;
    intmap[1] = 22;

    ft::map<int, int>::value_compare v_compare = intmap.value_comp();
    ft::map<int, int>::iterator tree = intmap.find(3);
    ft::map<int, int>::iterator two = intmap.find(2);

    std::cout << "map:\n" << intmap << std::endl;
    std::cout << "value_comp()([3, 42], [2, 32]): " << v_compare(*tree, *two) << std::endl;
}

static void test_value_comp_cplusplus() {
  ft::map<char,int> mymap;

  mymap['x']=1001;
  mymap['y']=2002;
  mymap['z']=3003;

  std::cout << "mymap contains:\n";

  ft::pair<char,int> highest = *mymap.rbegin();          // last element

  ft::map<char,int>::iterator it = mymap.begin();
  do {
    std::cout << it->first << " => " << it->second << '\n';
  } while ( mymap.value_comp()(*it++, highest) );

}

static void test_find() {
    println("test map find");

    ft::map<int, int> intmap;

    for (int i = 0; i < 10; i++) {
        intmap[i] = i;
    }
    std::cout << "find every element in the map" << std::endl;

    for (int i = 0; i < 10; i++) {
        ft::map<int, int>::iterator value = intmap.find(i);
        if (value != intmap.end())
            std::cout << *value << std::endl;
    }

    std::cout << "try find an non existent element" << std::endl;

    std::cout << "found 42: " << (intmap.find(42) != intmap.end()) << std::endl;
}

static void test_count() {
    println("test map count");

    ft::map<std::string, std::string> string_map;

    string_map["an element"];
    string_map["another element"];
    string_map["other element"];

    std::cout << "map count 'an element': " << string_map.count("an element") << std::endl;
    std::cout << "map count 'non existing element': " << string_map.count("non existing element") << std::endl;

    ft::map<int, int> map;
    std::cout << "count elements of an empty map: " << map.count(32) << std::endl;
}

static void test_lower_bound() {
    println("test map lower_bound");

    ft::map<char, std::string> string_map;

    string_map['a'] = "arara";
    string_map['e'] = "elefante";
    string_map['i'] = "indicador";
    string_map['o'] = "orca";
    string_map['u'] = "urubu";

    const ft::map<char, std::string> const_string_map = string_map;

    ft::map<char, std::string>::iterator iter = string_map.lower_bound('e');

    std::cout << "lower bound('e'): " << *iter << std::endl;
    std::cout << "lower bound('a'): " << *const_string_map.lower_bound('a') << std::endl;
    std::cout << "lower bound('u'): " << *const_string_map.lower_bound('u') << std::endl;
    iter = string_map.lower_bound('c');
    std::cout << "lower bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::map<char, std::string>::iterator nciter = const_string_map.lower_bound('e');
}

static void test_lower_bound_custom_comparator() {
    println("test map lower_bound");

    ft::map<char, std::string, CustomComparator<char> > string_map;

    string_map['a'] = "arara";
    string_map['e'] = "elefante";
    string_map['i'] = "indicador";
    string_map['o'] = "orca";
    string_map['u'] = "urubu";

    const ft::map<char, std::string, CustomComparator<char> > const_string_map = string_map;

    ft::map<char, std::string>::iterator iter = string_map.lower_bound('e');

    std::cout << "lower bound('e'): " << *iter << std::endl;
    std::cout << "lower bound('a'): " << *const_string_map.lower_bound('a') << std::endl;
    std::cout << "lower bound('u'): " << *const_string_map.lower_bound('u') << std::endl;
    iter = string_map.lower_bound('c');
    std::cout << "lower bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::map<char, std::string>::iterator nciter = const_string_map.lower_bound('e');
}

static void test_upper_bound() {
    println("test map upper_bound");

    ft::map<char, std::string> string_map;

    string_map['a'] = "arara";
    string_map['e'] = "elefante";
    string_map['i'] = "indicador";
    string_map['o'] = "orca";
    string_map['u'] = "urubu";

    const ft::map<char, std::string> const_string_map = string_map;


    std::cout << "upper bound('e'): " << *string_map.upper_bound('e') << std::endl;
    std::cout << "upper bound('a'): " << *string_map.upper_bound('a') << std::endl;
    std::cout
        << "upper bound('u') == end(): "
        << (const_string_map.upper_bound('u') == const_string_map.end())
        << std::endl;
    ft::map<char, std::string>::const_iterator iter;
    iter = const_string_map.upper_bound('c');
    std::cout << "upper bound('c'): " << *iter << std::endl;

    // shoudn't compile:
    // ft::map<char, std::string>::iterator nciter = const_string_map.upper_bound('e');
}

static void test_equal_range() {
    println("test equal range");

    typedef ft::map<char, std::string> map;
    map string_map;

    string_map['u'] = "urubu";
    string_map['o'] = "orca";
    string_map['i'] = "indicador";
    string_map['e'] = "elefante";
    string_map['a'] = "arara";

    const ft::map<char, std::string> const_string_map = string_map;

    ft::pair<map::const_iterator, map::const_iterator> result;

    result = const_string_map.equal_range('e');
    map::const_iterator first = result.first;
    map::const_iterator end = result.second;

    while (first != end) {
        std::cout << "result:\n" << *first << std::endl;
        ++first;
    }
    std::cout << "peek at the end:\n" << *end << std::endl;

    ft::pair<map::iterator, map::iterator> mut_result;
    mut_result = string_map.equal_range('a');

    std::cout << "search from a non const map" << std::endl;
    first = mut_result.first;
    end = mut_result.second;
    while (first != end) {
        std::cout << "result:\n" << *first << std::endl;
        ++first;
    }
    std::cout << "peek at the end:\n" << *end << std::endl;
    // shoudn't compile:
    // mut_result = const_string_map.equal_range('i');
}

static void test_get_allocator_cplusplus() {
    println("test get allocator from cplusplus");
    int psize;
    ft::map<char,int> mymap;
    ft::pair<const char,int>* p;

    // allocate an array of 5 elements using mymap's allocator:
    p=mymap.get_allocator().allocate(5);

    // assign some values to array
    psize = sizeof(ft::map<char,int>::value_type)*5;

    std::cout << "The allocated array has a size of " << psize << " bytes.\n";

    mymap.get_allocator().deallocate(p,5);
}

void testMap() {
    test_empty_constructor();
    test_range_constructor();
    test_copy_constructor();
    test_assignment_operator();
    test_begin();
    test_end();
    test_rbegin();
    test_rend();
    // test_reverse_iterator_quirks();
    test_empty();
    test_size();
    test_max_size();
    test_access_operator();
    test_access_operator_cplusplus();

    test_insert();
    test_insert_with_hint();
    test_insert_range();

    test_erase();
    test_erase_key();
    test_erase_range();
    test_erase_range_custom_comparator();
    test_erase_cplusplus();

    test_swap();
    test_clear();

    test_key_comp();
    test_value_comp();
    test_value_comp_cplusplus();

    test_find();
    test_count();

    test_lower_bound();
    test_lower_bound_custom_comparator();
    test_upper_bound();
    test_equal_range();

    test_get_allocator_cplusplus();
}

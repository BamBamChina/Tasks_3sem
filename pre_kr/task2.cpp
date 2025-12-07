#include <iostream>
#include <string>
#include <cctype>

template<typename ForwardIterator, typename UnaryFunction>
void transform_inplace(ForwardIterator first, ForwardIterator last, UnaryFunction func) {
    for (; first != last; ++first) {
        func(*first);
    }
}

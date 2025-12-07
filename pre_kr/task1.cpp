#include <algorithm>

template<typename ForwardIterator, typename UnaryPredicate>
ForwardIterator max_element_if(
    ForwardIterator first, ForwardIterator last, UnaryPredicate pred) {
    
    // Находим первый элемент, удовлетворяющий предикату
    ForwardIterator max_it = last;
    
    for (ForwardIterator it = first; it != last; ++it) {
        if (pred(*it)) {
            max_it = it;
            break;
        }
    }
    
    // Если не нашли ни одного подходящего элемента
    if (max_it == last) {
        return last;
    }
    
    // Ищем максимальный элемент среди удовлетворяющих предикату
    for (ForwardIterator it = max_it; it != last; ++it) {
        if (pred(*it) && *max_it < *it) {
            max_it = it;
        }
    }
    
    return max_it;
}

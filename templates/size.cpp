template<typename T, size_t N>
class Array {};

template<typename T, size_t N>
size_t size(const Array<T, N>&) {
    return N;
}

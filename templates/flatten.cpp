template<typename T>
class Array {};

template<typename T, typename Stream>
void flatten(const T& elem, Stream& out) {
    out << elem << " ";
}

template<typename U, typename Stream>
void flatten(const Array<U>& array, Stream& out) {
    for (const auto& elem : array) {
        flatten(elem, out); 
    }
}

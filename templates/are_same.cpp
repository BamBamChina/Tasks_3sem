template<typename... Types>
struct are_sames;  

template<typename T, typename U>
struct are_sames<T, U> {
    static const bool value = std::is_same<T, U>::value;
};

template<typename T, typename U, typename... Rest>
struct are_sames<T, U, Rest...> {
    static const bool value = 
        std::is_same<T, U>::value && are_sames<U, Rest...>::value;
};

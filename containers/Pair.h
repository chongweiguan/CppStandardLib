#include <iostream>

template <typename T, typename U>
class Pair {
public:
    T first;
    U second;

    Pair(T t, U u) : first(t), second(u) {};
    Pair() : first(), second() {};

    Pair(const Pair& other) = default;
    Pair& operator=(const Pair& other) = default;
    Pair(Pair&& other) = default;
    Pair& operator=(Pair&& other) = default;

    ~Pair() = default;

    template<typename V, typename W>
    friend bool operator<(const Pair<V,W>& p1, const Pair<V,W>& p2);

    template<typename V, typename W>
    friend bool operator<=(const Pair<V,W>& p1, const Pair<V,W>& p2);

    template<typename V, typename W>
    friend bool operator>(const Pair<V,W>& p1, const Pair<V,W>& p2);

    template<typename V, typename W>
    friend bool operator>=(const Pair<V,W>& p1, const Pair<V,W>& p2);

    template<typename V, typename W>
    friend bool operator==(const Pair<V,W>& p1, const Pair<V,W>& p2);

    template<typename V, typename W>
    friend std::ostream& operator<<(std::ostream& out, const Pair<V,W>& p);
};

template<typename T, typename U>
bool operator<(const Pair<T,U>& p1, const Pair<T,U>& p2) {
    if (p1.first == p2.first) return p1.second < p2.second;
    return p1.first < p2.first;
}

template<typename T, typename U>
bool operator<=(const Pair<T,U>& p1, const Pair<T,U>& p2) {
    if (p1.first == p2.first) return p1.second <= p2.second;
    return p1.first <= p2.first;
}

template<typename T, typename U>
bool operator>(const Pair<T,U>& p1, const Pair<T,U>& p2) {
    if (p1.first == p2.first) return p1.second > p2.second;
    return p1.first > p2.first;
}

template<typename T, typename U>
bool operator>=(const Pair<T,U>& p1, const Pair<T,U>& p2) {
    if (p1.first == p2.first) return p1.second >= p2.second;
    return p1.first >= p2.first;
}

template<typename T, typename U>
bool operator==(const Pair<T,U>& p1, const Pair<T,U>& p2) {
    return p1.first == p2.first && p1.second == p2.second;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& out, const Pair<T,U>& p) {
    out << "(" << p.first << "," << p.second << ")";
    return out;
}
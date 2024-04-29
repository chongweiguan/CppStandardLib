template <typename T, typename U>
class Pair {
public:
    const T first;
    const U second;

    Pair(T t, U u) : first(t), second(u) {}

    bool operator<(const Pair& other) const {
        if (other.first == first) return second < other.second;
        return first < other.first;
    }
};
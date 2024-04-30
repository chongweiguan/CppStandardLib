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

    bool operator<(const Pair& other) const {
        if (other.first == first) return second < other.second;
        return first < other.first;
    }
};
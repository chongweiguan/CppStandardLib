#include <initializer_list>
#include <iterator>

template<typename T, size_t N>
class Array {
private:
    T t_array[N]{};

public:
    
    // Constructor using initializer_list
    Array(std::initializer_list<T> list) {
        if (list.size() > N) throw std::out_of_range("Initializer list too large");
        std::copy(list.begin(), list.end(), t_array);
    }

    // default constructor
    Array() = default;

    // default destructor
    ~Array() = default;

    // Copy constructor
    Array(const Array& other) {
        for (int i = 0; i < N; ++i) {
            t_array[i] = other[i];
        }
    }

    // Copy assigment
    Array& operator=(const Array& other) {
        if (&other == this) return *this;
        for (int i = 0; i < N; ++i) {
            t_array[i] = other[i];
        }
        return *this;
    }

    Array(Array&& other) = default;
    Array& operator=(Array&& other) = default;

    // Access specified element
    T& operator[](int index) {
        return t_array[index];
    }

    // Access specified const element
    const T& operator[](int index) const {
        return t_array[index];
    }

    // Access specified element with bounds checking
    T& at(int index) {
        if (list.size() > N) throw std::out_of_range("Initializer list too large");
        return t_array[index];
    }

    // Access const specified element with bounds checking
    const T& at(int index) const {
        if (list.size() > N) throw std::out_of_range("Initializer list too large");
        return t_array[index];
    }

    // Access first element
    T front() const {
        return t_array[0];
    }

    // Access last element
    T back() const {
        return t_array[N - 1];
    }

    // Access to the underlying contiguous storage
    T* data() {
        return &t_array[0];
    }

    // Access to the const underlying contiguous storage
    const T* data() const {
        return &t_array[0];
    }
    
    // Returns an Iterator to the first element of the array
    T* begin() {
        return &t_array[0];
    }

    // Returns a const Iterator to the first element of the array
    const T* cbegin() const {
        return &t_array[0];
    }

    // Returns an Iterator to the position after the last element of the array
    T* end() {
        return &t_array[N];
    } 

    // Returns a const Iterator to the position after the last element of the array
    const T* cend() const {
        return &t_array[N];
    }

    // Returns a reverse Iterator to the position last element of the array
    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator(&t_array[N]);
    }

    // Returns an Iterator to the position before the first element of the array
    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator(&t_array[0]);
    }

    // Returns a reverse Iterator to the position last element of the array
    const std::reverse_iterator<T*> crbegin() const {
        return std::reverse_iterator(&t_array[N]);
    }

    // Returns an Iterator to the position before the first element of the array
    const std::reverse_iterator<T*> crend() const {
        return std::reverse_iterator(&t_array[0]);
    }

    // Checks whether the array is empty;
    bool empty() const {
        return N == 0;
    }

    // returns the size of the array
    size_t size() const {
        return N;
    }

    // returns the maximum possible number of elements
    size_t max_size() const {
        return N;
    }

    // fills the container with specified value
    void fill (const T t) {
        for (int i = 0; i < N; i++) {
            t_array[i] = t;
        }
    }
};
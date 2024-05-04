#pragma once

#include <initializer_list>
#include <iterator>

template<typename T, size_t N>
class Array {
private:
    T* _data;

public:
    // default constructor
    Array() {
        if (N > max_size()) throw std::range_error("N is too large");
        _data = new T[N];
    }

    // Constructor using initializer_list
    Array(std::initializer_list<T> list) {
        if (N > max_size()) throw std::range_error("size is too large");
        if (list.size() > N) throw std::out_of_range("Initializer list too large");
        _data = new T[N];
        std::copy(list.begin(), list.end(), _data);
    }

    // default destructor
    ~Array() {
        delete[] _data;
    }

    // Copy constructor
    Array(const Array& other) {
        _data = new T[N];
        for (int i = 0; i < N; ++i) {
            _data[i] = other[i];
        }
    }

    // Copy assigment
    Array& operator=(const Array& other) {
        if (&other == this) return *this;
        for (int i = 0; i < N; ++i) {
            _data[i] = other[i];
        }
        return *this;
    }

    Array(Array&& other) {
        _data = new T[N];
        for (int i = 0; i < N; ++i) {
            _data[i] = other[i];
        }

    }
    Array& operator=(Array&& other) {
        T* _newData = new T[N];
        for (int i = 0; i < N; ++i) {
            _newData[i] = other[i];
        }
        delete[] _data;
        _data = _newData;
        return *this;
    }

    // Access specified element
    T& operator[](int index) {
        return _data[index];
    }

    // Access specified const element
    const T& operator[](int index) const {
        return _data[index];
    }

    // Access specified element with bounds checking
    T& at(int index) {
        if (index >= N || index < 0) throw std::out_of_range("Invalid index");
        return _data[index];
    }

    // Access const specified element with bounds checking
    const T& at(int index) const {
        if (index >= N || index < 0) throw std::out_of_range("Invalid index");
        return _data[index];
    }

    size_t max_size() {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    // Access first element
    T front() const {
        return _data[0];
    }

    // Access last element
    T back() const {
        return _data[N - 1];
    }

    // Access to the underlying contiguous storage
    T* data() {
        return &_data[0];
    }

    // Access to the const underlying contiguous storage
    const T* data() const {
        return &_data[0];
    }
    
    // Returns an Iterator to the first element of the array
    T* begin() {
        return &_data[0];
    }

    // Returns a const Iterator to the first element of the array
    const T* cbegin() const {
        return &_data[0];
    }

    // Returns an Iterator to the position after the last element of the array
    T* end() {
        return &_data[N];
    } 

    // Returns a const Iterator to the position after the last element of the array
    const T* cend() const {
        return &_data[N];
    }

    // Returns a reverse Iterator to the position last element of the array
    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator(&_data[N]);
    }

    // Returns an Iterator to the position before the first element of the array
    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator(&_data[0]);
    }

    // Returns a reverse Iterator to the position last element of the array
    const std::reverse_iterator<T*> crbegin() const {
        return std::reverse_iterator(&_data[N]);
    }

    // Returns an Iterator to the position before the first element of the array
    const std::reverse_iterator<T*> crend() const {
        return std::reverse_iterator(&_data[0]);
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
            _data[i] = t;
        }
    }

    template<typename V, size_t S>
    friend bool operator<(const Array<V,S>& a1, const Array<V,S>& a2);

    template<typename V, size_t S>
    friend bool operator<=(const Array<V,S>& a1, const Array<V,S>& a2);

    template<typename V, size_t S>
    friend bool operator>(const Array<V,S>& a1, const Array<V,S>& a2);

    template<typename V, size_t S>
    friend bool operator>=(const Array<V,S>& a1, const Array<V,S>& a2);

    template<typename V, size_t S>
    friend bool operator==(const Array<V,S>& a1, const Array<V,S>& a2);
};

template<typename V, size_t S>
bool operator<(const Array<V,S>& a1, const Array<V,S>& a2) {
    for (int i = 0; i < S; ++i) {
        if (a1[i] >= a2[i]) return false;
    }
    return true;
}

template<typename V, size_t S>
bool operator<=(const Array<V,S>& a1, const Array<V,S>& a2) {
    for (int i = 0; i < S; ++i) {
        if (a1[i] > a2[i]) return false;
    }
    return true;
}

template<typename V, size_t S>
bool operator>(const Array<V,S>& a1, const Array<V,S>& a2) {
    return !(a1 <= a2);
}

template<typename V, size_t S>
bool operator>=(const Array<V,S>& a1, const Array<V,S>& a2) {
    return !(a1 < a2);
}

template<typename V, size_t S>
bool operator==(const Array<V,S>& a1, const Array<V,S>& a2) {
    for (int i = 0; i < S; ++i) {
        if (a1[i] != a2[i]) return false;
    }
    return true;
}
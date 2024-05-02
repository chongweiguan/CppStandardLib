#include <initializer_list>
#include <iterator>

template<typename T>
class Vector {
private:
    T* _arr;
    size_t _capacity;
    size_t _size;

public:
    // Constructor with size
    Vector(size_t size) : _capacity(size), _size(size), _arr(new T[size]{}) {};
    
    // Constructor with size and default input
    Vector(size_t size, T t) : _capacity(size), _size(size) {
        _arr = new T[size];
        for (size_t i = 0; i < size; i++) {
            _arr[i] = new T(t);
        }
    }

    // Constructor with initializer_list
    Vector(std::initializer_list<T> list) {
        size_t size = list.size();
        _arr = new T[size];
        std::copy(list.begin(), list.end(), _arr);
        _size = size;
        _capacity = size;
    }

    // Copy constructor
    Vector(const Vector& vector) : _capacity(vector.capacity()), _size(vector.size()) {
        _arr = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            _arr[i] = vector[i];
        }
    }

    // Copy assignment
    Vector& operator=(const Vector& vector) {
        T* newArr = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            newArr[i] = vector[i];
        }
        _capacity = vector.capacity();
        _size = vector.size();

        delete[] _arr;
        _arr = newArr;
        return *this;
    }

    // move constructor
    Vector(Vector&& vector) : _capacity(vector.capacity()), _size(vector.size()) {
        _arr = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            _arr[i] = vector[i];
        }
        vector._capacity = 0;
        vector._size = 0;
        delete[] vector._arr;
    }

    // move assignment
    Vector& operator=(Vector&& vector) {
        T* newArr = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            newArr[i] = vector[i];
        }
        _capacity = vector.capacity();
        _size = vector.size();

        delete[] _arr;
        _arr = newArr;
        delete [] vector._arr;
        vector._size = 0;
        vector._capacity = 0;
        return *this;
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _capacity;
    }

    bool empty() {
        return _size == 0;
    }

    T& operator[](int index) {
        return _arr[index];
    }

    const T& operator[](int index) const {
        return _arr[index];
    }

    T& at(int index) {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        return _arr[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        return _arr[index];
    }

    T front() {
        return _arr[0];
    }

    T back() {
        return _arr[_size-1];
    }

    T* begin() {
        return &_arr[0];
    }

    T* end() {
        return &_arr[_size-1];
    }

    const T* cbegin() const {
        return &_arr[0];
    }

    const T* cend() const {
        return &_arr[_size-1];
    }
};
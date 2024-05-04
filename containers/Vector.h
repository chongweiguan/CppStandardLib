#include <initializer_list>
#include <iterator>
#include <algorithm>

template<typename T>
class Vector {
private:
    T* _data;
    size_t _capacity;
    size_t _size;

public:
    // Default constructor
    Vector() = default;

    // Constructor with size
    Vector(size_t size) : _capacity(size), _size(size) {
        if (size > max_size()) throw std::range_error("size is too large");
        _data(new T[size]{});
    }
    
    // Constructor with size and default input
    Vector(size_t size, T t) : _capacity(size), _size(size) {
        if (size > max_size()) throw std::range_error("size is too large");
        _data = new T[size];
        for (size_t i = 0; i < size; i++) {
            _data[i] = new T(t);
        }
    }

    // Constructor with initializer_list
    Vector(std::initializer_list<T> list) {
        if (list.size() > max_size()) throw std::out_of_range("Initializer list too large");
        size_t size = list.size();
        _data = new T[size];
        std::copy(list.begin(), list.end(), _data);
        _size = size;
        _capacity = size;
    }

    // Copy constructor
    Vector(const Vector& vector) : _capacity(vector.capacity()), _size(vector.size()) {
        _data = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            _data[i] = vector[i];
        }
    }

    // Copy assignment
    Vector& operator=(const Vector& vector) {
        T* newData = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            newData[i] = vector[i];
        }
        _capacity = vector.capacity();
        _size = vector.size();

        delete[] _data;
        _data = newData;
        return *this;
    }

    // move constructor
    Vector(Vector&& vector) : _capacity(vector.capacity()), _size(vector.size()) {
        _data = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            _data[i] = vector[i];
        }
        vector._capacity = 0;
        vector._size = 0;
        delete[] vector._data;
    }

    // move assignment
    Vector& operator=(Vector&& vector) {
        T* newData = new T[vector.size()];
        for (int i = 0; i < vector.size(); ++i) {
            newData[i] = vector[i];
        }
        _capacity = vector.capacity();
        _size = vector.size();

        delete[] _data;
        _data = newData;
        delete [] vector._data;
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
        return _data[index];
    }

    const T& operator[](int index) const {
        return _data[index];
    }

    size_t max_size() const {
        return std::numeric_limits<size_t>::max() / sizeof(T);
    }

    T& at(int index) {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        return _data[index];
    }

    const T& at(int index) const {
        if (index < 0 || index >= _size) throw std::out_of_range("Invalid index");
        return _data[index];
    }

    T front() {
        return _data[0];
    }

    T back() {
        return _data[_size-1];
    }

    T* data() {
        return &_data[0];
    }

    T* begin() {
        return &_data[0];
    }

    T* end() {
        return &_data[_size];
    }

    const T* cbegin() const {
        return &_data[0];
    }

    const T* cend() const {
        return &_data[_size];
    }

    std::reverse_iterator<T*> rbegin() {
        return std::reverse_iterator<T*>(&_data[_size]);
    }

    std::reverse_iterator<T*> rend() {
        return std::reverse_iterator<T*>(&_data[0]);
    }

    const std::reverse_iterator<T*> crbegin() const {
        return std::reverse_iterator<T*>(&_data[_size]);
    }

    const std::reverse_iterator<T*> crend() const{
        return std::reverse_iterator<T*>(&_data[0]);
    }

    void resize(size_t n, T obj = {}) {
        if (n > max_size()) throw std::range_error("size is too large");
        if (n <= _size) {
            _size = n;
            return;
        }
        if (n <= _capacity) {
            for (size_t i = _size; i < n; ++i) {
                _data[i] = obj;
            }
            return;
        }
        while (_capacity < n) _capacity *= 2;
        T* newData = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        for (size_t i = _size; i < n; ++i) {
            newData[i] = obj;
        }

        delete[] _data;
        _data = newData;
        _size = n;
    }

    void reserve(size_t n) {
        if (n > max_size()) throw std::range_error("size is too large");
        if (n <= _capacity) return;

        while (_capacity < n) _capacity *= 2;
         T* newData = new T[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            newData[i] = _data[i];
        }
        delete[] _data;
        _data = newData;
    }

    void assign(size_t n, T data) {
        if (n > max_size()) throw std::range_error("size is too large");
        T* newData = new T[n];
        for (size_t i = 0; i < n; ++i) {
            newData[i] = data;
        }
        delete[] _data;
        _data = newData;
    }

    void assign(T* begin, T* end) {
        int n = end - begin;
        if (n > max_size()) throw std::range_error("size is too large");

        T* newData = new T[n];
        std::copy(begin, end, newData);
        delete[] _data;
        _data = newData;
    }

    void assign(std::initializer_list<T> list) {
        int n = list.size();
        if (n > max_size()) throw std::range_error("size is too large");
        T* newData = new T[n];
        std::copy(list.begin(), list.end(), newData);
        delete[] _data;
        _data = newData;
    }

    void push_back(T t) {
        if (_size == _capacity) {
            _capacity *= 2;
            T* newData = new T[_capacity];
            for (int i = 0; i < _size; ++i) {
                newData[i] = _data[i];
            }
            delete[] _data;
            _data = newData;
        }
        _data[_size] = t;
        ++_size;
    }

    void pop_back() {
        if (_size == 0) throw std::range_error("No element in vector");
        --_size;
    }

    void clear() {
        _size = 0;
    }

    void swap(Vector& other) {
        T* temp = _data;
        size_t t_size = _size;
        size_t t_capacity = _capacity;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        other._data = temp;
        other._size = t_size;
        other._capacity = t_capacity;
    }

    T* erase(T* ptr) {
        while (ptr+1 != end()) {
            *ptr = *(ptr+1);
            ++ptr;
        }
        --_size;
        return ptr;
    }

    T* erase(T* p_start, T* p_end) {
        while (p_end != end()) {
            *p_start = *(p_end);
            ++p_end;
            ++p_start;
        }
        _size -= (p_end - p_start);
        return p_start;
    }

    template<typename... Args>
    T* emplace(T* ptr, Args&&... args) {
        return ptr;
    }

    template<typename... Args>
    void emplace_back(T* ptr, Args&&... args) {
        return;
    }
};
#include <cstring>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <iostream>

class String {
private:
    char* data;
    size_t _N;
    size_t _capacity;

public:
    String() : data(nullptr), _N(0) {}

    String(const String& s) {
        data = new char[s._N];
        for (size_t i = 0; i < s._N; ++i) {
            data[i] = s.data[i];
        }
        _N = s._N;
        _capacity = s._capacity;
    }

    String(String& s, size_t pos, size_t len) {
        if (pos + len > s._N) throw std::out_of_range("Out of bounds");
        data = new char[len];
        for (size_t i = pos; i < pos + len; ++i) {
            data[i-pos] = s.data[i];
        }
        _N = len;
        _capacity = len;
    }

    String(const char* s) {
        _N = std::strlen(s);
        _capacity = _N;
        data = new char[_N];
        for (size_t i = 0; i < _N; ++i) {
            data[i] = s[i];
        }
    }

    String(const char* s, size_t n) {
        _N = std::min(n, std::strlen(s));
        data = new char[_N];
        for (size_t i = 0; i < _N; ++i) {
            data[i] = s[i];
        }
        _capacity = _N;
    }

    String(size_t n, char c) {
        _N = n;
        data = new char[_N];
        for (size_t i = 0; i < n; ++i) {
            data[i] = c;
        }
        _capacity = _N;
    }

    String(std::initializer_list<char> list) {
        _N = list.size();
        data = new char[_N];
        std::copy(list.begin(), list.end(), data);
        _capacity = _N;
    }

    String(String&& s) noexcept {
        _N = s._N;
        data = new char[_N];
        for (size_t i = 0; i < _N; ++i) {
            data[i] = s.data[i];
        }
        _capacity = _N;
    }

    String(char* begin, char* end) {
        _N = end - begin;
        data = new char[_N];
        for (size_t i = 0; i < _N; ++i) {
            data[i] = *begin;
            ++begin;
        }
    }

    ~String() {
        std::cout << "String destructor" << std::endl;
        delete[] data;
    }

    String& operator=(const String& s) {
        if (this != &s) {
            delete[] data;
            _N = s._N;
            data = new char[_N];

            for (int i = 0; i < _N; ++i) {
                data[i] = s.data[i];
            }
            _capacity = _N;
        }
        return *this;
    }

    String& operator=(const char* s) {
        delete[] data;
        _N = strlen(s);

        data = new char[_N];
        for (int i = 0; i < _N; ++i) {
            data[i] = s[i];
        }
        _capacity = _N;
        return *this;
    }

    String& operator=(char c) {
        delete[] data;
        data = new char[1];
        data[0] = c;
        _capacity = 1;
        _N = 1;
        return *this;
    }

    String& operator=(std::initializer_list<char> list) {
        delete[] data;
        _N = list.size();
        data = new char[_N];
        std::copy(list.begin(), list.end(), data);
        _capacity = _N;
        return *this;
    }

    String& operator=(String&& s) noexcept {
        delete[] data;
        _N = s._N;
        data = new char[_N];
        for (int i = 0; i < _N; ++i) {
            data[i] = s.data[i];
        }
        _capacity = _N;
        return *this;
    }

    char* begin() {
        return &data[0];
    }

    char* end() {
        return &data[_N];
    }

    const char* cbegin() const {
        return &data[0];
    }

    const char* cend() const {
        return &data[_N];
    }

    std::reverse_iterator<char*> rbegin() {
        return std::reverse_iterator(&data[_N]);
    }

    std::reverse_iterator<char*> rend() {
        return std::reverse_iterator(&data[0]);
    }

    const std::reverse_iterator<char*> crbegin() const {
        return std::reverse_iterator(&data[_N]);
    }

    const std::reverse_iterator<char*> crend() const {
        return std::reverse_iterator(&data[0]);
    }


    size_t size() const {
        return _N;
    }

    size_t length() const {
        return _N;
    }

    size_t max_size() const {
        return std::numeric_limits<size_t>::max() / sizeof(char);
    }

    size_t capacity() const {
        return strlen(data);
    }

    void reserve(size_t n) {
        if (n > max_size()) throw std::range_error("size is too large");
        if (n <= _capacity) return;

        while (_capacity < n) _capacity *= 2;
        char* newData = new char[_capacity];
        for (size_t i = 0; i < _N; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    void clear() {
        delete[] data;
        _N = 0;
        _capacity = 0;
    }

    bool empty() const {
        return _N == 0;
    }

    void shrink_to_fit(size_t n) {
        if (n > max_size()) throw std::range_error("size is too large");
        if (n >= _capacity) return;

        char* newData = new char[n];
        for (size_t i = 0; i < n; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    char& operator[](size_t pos) {
        return data[pos];
    }

    const char& operator[](size_t pos) const {
        return data[pos];
    }

    char& at(size_t pos) {
        if (pos < 0 || pos >= _N) throw std::out_of_range("Invalid index");
        return data[pos];
    }

    const char& at(size_t pos) const {
        if (pos < 0 || pos >= _N) throw std::out_of_range("Invalid index");
        return data[pos];
    }

    char& back() {
        return data[_N-1];
    }

    const char& back() const {
        return data[_N-1];
    }

    char& front() {
        return data[0];
    }

    const char& front() const {
        return data[0];
    }

    friend std::ostream& operator<<(std::ostream& out, const String& s);
};

std::ostream& operator<<(std::ostream& out, const String& s) {
    for (size_t i = 0; i < s._N; ++i) {
        out << s.data[i];
    }
    return out;
}
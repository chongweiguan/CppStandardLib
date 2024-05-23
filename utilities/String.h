#include <cstring>
#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <iostream>

class String {
private:
    char* data;
    size_t size;

public:
    String() : data(nullptr), size(0) {}

    String(const String& s) {
        data = new char[s.size];
        for (size_t i = 0; i < s.size; ++i) {
            data[i] = s.data[i];
        }
        size = s.size;
    }

    String(String& s, size_t pos, size_t len) {
        if (pos + len > s.size) throw std::out_of_range("Out of bounds");
        data = new char[len];
        for (size_t i = pos; i < pos + len; ++i) {
            data[i-pos] = s.data[i];
        }
        size = len;
    }

    String(const char* s) {
        size = std::strlen(s);
        data = new char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = s[i];
        }
    }

    String(const char* s, size_t n) {
        size = std::min(n, std::strlen(s));
        data = new char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = s[i];
        }
    }

    String(size_t n, char c) {
        size = n;
        data = new char[size];
        for (size_t i = 0; i < n; ++i) {
            data[i] = c;
        }
    }

    String(std::initializer_list<char> list) {
        size = list.size();
        data = new char[size];
        std::copy(list.begin(), list.end(), data);
    }

    String(String&& s) noexcept {
        size = s.size;
        data = new char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = s.data[i];
        }
    }

    String(char* begin, char* end) {
        size = end - begin;
        data = new char[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = *begin;
            ++begin;
        }
    }

    char* begin() {
        return &data[0];
    }

    char* end() {
        return &data[size];
    }

    friend std::ostream& operator<<(std::ostream& out, const String& s);
};

std::ostream& operator<<(std::ostream& out, const String& s) {
    for (size_t i = 0; i < s.size; ++i) {
        out << s.data[i];
    }
    return out;
}
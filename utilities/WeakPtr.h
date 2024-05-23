#pragma once
#include "SharedPtr.h"

template<typename T>
class WeakPtr {
private:
    T* resource;
    int* count;

public:
    WeakPtr() : resource(nullptr), count(nullptr) {}
    WeakPtr(const SharedPtr<T>& shared_ptr) : resource(shared_ptr.resource), count(shared_ptr.count) {}
    WeakPtr(const WeakPtr& weak_ptr) : resource(weak_ptr.resource), count(weak_ptr.count) {}
    ~WeakPtr() {}

    WeakPtr& operator=(const WeakPtr& weak_ptr) {
        if (this == &weak_ptr || weak_ptr.resource == resource) return *this;
        resource = weak_ptr.resource;
        count = weak_ptr.count;
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& shared_ptr) {
        if (resource == shared_ptr.resource) return *this;
        resource = shared_ptr.resource;
        count = shared_ptr.count;
        return *this;
    }

    void swap(WeakPtr& other) noexcept {
        if (resource != other.resource) {
            T* temp = resource;
            int* tempCount = count;

            resource = other.resource;
            count = other.count;

            other.resource = temp;
            other.count = tempCount;
        }
    }

    void reset() noexcept {
        resource = nullptr;
        count = nullptr;
    }

    int use_count() const noexcept {
        if (count == nullptr) return 0;
        return *count;
    }

    bool expired() const noexcept {
        return use_count() == 0;
    }

    SharedPtr<T> lock() {
        SharedPtr<T> shared_ptr;
        shared_ptr.resource = resource;
        shared_ptr.count = count;
        ++*count;
        return shared_ptr;
    }
};

template<typename T>
void swap(WeakPtr<T>& wp1, WeakPtr<T>& wp2) {
    if (wp1.resource != wp2.resource) {
        T* tempR = wp1.resource;
        int* tempC = wp1.count;

        wp1.resource = wp2.resource;
        wp1.count = wp1.count;
    }
}
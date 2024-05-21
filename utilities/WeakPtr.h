#pragma once
#include "SharedPtr.h"

template<typename T>
class WeakPtr {
private:
    SharedPtr<T>* m_ptr;

public:
    WeakPtr() : m_ptr(nullptr) {}

    WeakPtr(SharedPtr<T>& shared_ptr) : m_ptr(&shared_ptr) {}

    WeakPtr(WeakPtr& weak_ptr) : m_ptr(weak_ptr.m_ptr) {}
    ~WeakPtr() {}

    WeakPtr& operator=(const WeakPtr& weak_ptr) {
        if (this == &weak_ptr || weak_ptr.m_ptr == m_ptr) return *this;
        m_ptr = weak_ptr.m_ptr;
        return *this;
    }

    WeakPtr& operator=(const SharedPtr<T>& shared_ptr) {
        if (m_ptr != &shared_ptr) {
            m_ptr = &shared_ptr;
        }
        return *this;
    }

    void swap(WeakPtr& other) noexcept {
        SharedPtr<T>* temp = m_ptr;
        m_ptr = other.m_ptr;
        other.m_ptr = temp;
    }

    void reset() noexcept {
        m_ptr = nullptr;
    }

    int use_count() const noexcept {
        return m_ptr->use_count();
    }

    bool expired() const noexcept {
        return m_ptr == nullptr || m_ptr->use_count() == 0;
    }

    SharedPtr<T>& lock() {
        return *m_ptr;
    }
};
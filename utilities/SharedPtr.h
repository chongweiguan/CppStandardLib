#pragma once
#include <iostream>

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
private:
    T* resource;
    int* count;

public:
    friend class WeakPtr<T>;

    SharedPtr() : resource{nullptr}, count{new int(0)} {}

    SharedPtr(T* resource) : resource(resource), count(new int(1)) {}

    SharedPtr(const SharedPtr& sharedPtr) {
        resource = sharedPtr.resource;
        count = sharedPtr.count;
        ++*count;
    }

    SharedPtr& operator=(const SharedPtr& sharedPtr) {
        if (this != &sharedPtr && sharedPtr.resource != resource) {
            --*count;
            if (*count <= 0) {
                if (resource != nullptr) delete resource;
                delete count;
            }

            resource = sharedPtr.resource;
            count = sharedPtr.count;
            ++*count;
        }
        return *this;
    }

    SharedPtr(SharedPtr&& sharedPtr) {
        resource = sharedPtr.resource;
        count = sharedPtr.count;
        sharedPtr.resource = nullptr;
        sharedPtr.count = new int(0);
    }

    SharedPtr& operator=(SharedPtr&& sharedPtr) {
        if (this != &sharedPtr) {

            if (--*count <= 0) {
                if (resource != nullptr) delete resource;
                delete count;
            }

            resource = sharedPtr.resource;
            count = sharedPtr.count;
            sharedPtr.resource = nullptr;
            sharedPtr.count = new int(0);
        }
        return *this;
    }

    ~SharedPtr() {
        --*count;
        if (*count <= 0) {
            if (resource != nullptr) delete resource;
            delete count;
        }
    }

    T* operator->() {
        return resource;
    }

    const T* operator->() const {
        return resource;
    }

    T& operator*() {
        return *resource;
    }

    const T& operator*() const {
        return *resource;
    }

    T* get() {
        return resource;
    }

    const T* get() const {
        return resource;
    }

    void swap(SharedPtr& ptr) {
        if (resource != ptr.resource) {
            T* temp = resource;
            int* tempCount = count;

            resource = ptr.resource;
            count = ptr.count;

            ptr.resource = temp;
            ptr.count = tempCount;
        }
    }

    void reset(T* newResource = nullptr) {
        --*count;
        if (*count == 0) {
            if (resource != nullptr) delete resource;
            delete count;
        }
        resource = newResource;
        if (newResource) {
            count = new int(1);  // Reset the count for the new resource
        } else {
            count = new int(0);
        }
    }

    int use_count() {
        return *count;
    }

    bool unique() {
        return *count == 1;
    }

    explicit operator bool() const {
        return resource != nullptr;
    }

    template<typename U>
    friend void swap(SharedPtr<U> ptr1, SharedPtr<U> ptr2) noexcept;

    template<typename V>
    friend bool operator==(const SharedPtr<V>& v1, const SharedPtr<V>& v2); 

    template<typename V>
    friend bool operator!=(const SharedPtr<V>& v1, const SharedPtr<V>& v2); 

    template<typename V>
    friend bool operator<(const SharedPtr<V>& v1, const SharedPtr<V>& v2);

    template<typename V>
    friend bool operator<=(const SharedPtr<V>& v1, const SharedPtr<V>& v2);

    template<typename V>
    friend bool operator>(const SharedPtr<V>& v1, const SharedPtr<V>& v2);

    template<typename V>
    friend bool operator>=(const SharedPtr<V>& v1, const SharedPtr<V>& v2);
};

template<typename U>
void swap(SharedPtr<U> ptr1, SharedPtr<U> ptr2) noexcept {
    if (ptr1.resource != ptr2.resource) {
        U* temp = ptr1.resource;
        U* tempCount = ptr1.count;

        ptr1.resource = ptr2.resource;
        ptr1.count = ptr2.count;

        ptr2.resource = temp;
        ptr2.count = tempCount;
    }
}

template<typename U, typename... Args>
SharedPtr<U> make_shared(Args&&... args) {
    U* u = new U(std::forward<Args>(args)...);
    return SharedPtr<U>(u);
}

template<typename V>
bool operator>=(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 >= *v2;
}

template<typename V>
bool operator==(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 == *v2;
}

template<typename V>
bool operator>(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 > *v2;
}

template<typename V>
bool operator<=(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 <= *v2;
}

template<typename V>
bool operator<(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 < *v2;
}

template<typename V>
bool operator!=(const SharedPtr<V>& v1, const SharedPtr<V>& v2) {
    return *v1 != *v2;
}

/*

Undefined functions
1. owner_before
2. allocate_shared
3. static_pointer_cast
4. dynamic_pointer_cast
5. const_pointer_cast
6. get_deleter

*/
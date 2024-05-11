#include <iostream>

template<typename T>
class SharedPtr {
private:
    T* resource;
    int* count;

public:
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
                delete resource;
                delete count;
            }

            resource = sharedPtr.resource;
            count = sharedPtr.count;
            ++*count;
        }
        return *this;
    }

    ~SharedPtr() {
        --*count;
        if (*count == 0) {
            delete resource;
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
        if (*count == 0) delete resource;
        resource = newResource;
    }

    int use_count() {
        return *count;
    }

    bool unique() {
        return *count == 1;
    }

    explicit operator bool() const {
        std::cout << "hello?";
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
    if (ptr1.resouce != ptr2.resouce) {
        U* temp = ptr1.resource;
        U* tempCount = ptr1.count;

        ptr1.resouce = ptr2.resouce;
        ptr1.count = ptr2.count;

        ptr2.resouce = temp;
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
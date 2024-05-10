template<typename T>
class UniquePtr {
private:
    T* resource;

public:

    UniquePtr() : resource(nullptr) {};

    UniquePtr(T* t) : resource(t) {}

    UniquePtr(UniquePtr&& other) : resource(other.resource) {
        other.resource = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        if (this != &other) {
            delete resource;
            resource = other.resource;
            other.resource = nullptr;
        }
        return *this;
    }

    ~UniquePtr() {
        delete resource;
    }

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    T* operator->() {
        return resource;
    }

    const T* operator->() const {
        return resource;
    }

    T* get() {
        return resource;
    }

    const T* get() const {
        return resource;
    }

    T& operator*() {
        return *resource;
    }

    const T& operator*() const{
        return *resource;
    }

    explicit operator bool() const {
        return resource != nullptr;
    }

    T* release() {
        T* res = resource;
        resource = nullptr;

        return res;
    }

    void reset(T* newResource = nullptr) {
        delete resource;
        resource = newResource;
    }

    template<typename U>
    friend void swap(UniquePtr<U>& ptr1, UniquePtr<U>& ptr2) noexcept;

    template<typename V>
    friend bool operator==(const UniquePtr<V>& v1, const UniquePtr<V>& v2); 

    template<typename V>
    friend bool operator!=(const UniquePtr<V>& v1, const UniquePtr<V>& v2); 

    template<typename V>
    friend bool operator<(const UniquePtr<V>& v1, const UniquePtr<V>& v2);

    template<typename V>
    friend bool operator<=(const UniquePtr<V>& v1, const UniquePtr<V>& v2);

    template<typename V>
    friend bool operator>(const UniquePtr<V>& v1, const UniquePtr<V>& v2);

    template<typename V>
    friend bool operator>=(const UniquePtr<V>& v1, const UniquePtr<V>& v2);
};

template<typename U>
void swap(UniquePtr<U>& ptr1, UniquePtr<U>& ptr2) noexcept {
    U* temp = ptr1.resource;
    ptr1.resource = ptr2.resource;
    ptr2.resource = temp;
}

template<typename V>
bool operator>=(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 >= *v2;
}

template<typename V>
bool operator==(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 == *v2;
}

template<typename V>
bool operator>(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 > *v2;
}

template<typename V>
bool operator<=(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 <= *v2;
}

template<typename V>
bool operator<(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 < *v2;
}

template<typename V>
bool operator!=(const UniquePtr<V>& v1, const UniquePtr<V>& v2) {
    return *v1 != *v2;
}

template<typename V, typename... Args>
auto make_unique(Args&&... args) {
    V* t = new V(std::forward<Args>(args)...);
    return UniquePtr<V>(t);
};
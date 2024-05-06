template<typename T>
class UniquePtr {
private:
    T* resource;

public:
    UniquePtr(T* resource) : resource(resource) {}

    UniquePtr(UniquePtr&& other) {
        resource = other.resource;
        other.resource = nullptr;
    }

    UniquePtr& operator=(UniquePtr&& other) {
        resource = other.resource;
        other.resource = nullptr;
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

    T operator*() {
        return *resource;
    }

    const T operator*() const{
        return *resource;
    }
};
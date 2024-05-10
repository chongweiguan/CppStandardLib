#include <iostream>

template<typename T>
class SharedPtr {
private:
    T* resource;
    int* count;

public:
    SharedPtr(T* resource) : resource(resource), count(new int(1)) {}

    SharedPtr(const SharedPtr& sharedPtr) {
        resource = sharedPtr.resource;
        count = sharedPtr.count;
        ++*count;
    }

    SharedPtr& operator=(const SharedPtr& sharedPtr) {
        if (this != &sharedPtr && sharedPtr.resource != resource) {
            --*count;
            if (*count == 0) {
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
};
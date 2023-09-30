#include <bits/stdc++.h>

//using namespace std;

template <typename T>
class UniquePtr {
private:
    T* ptr;
    explicit UniquePtr(T* ptr) : ptr(ptr) {}
public:
    static UniquePtr make_unique(T* ptr) {
        return UniquePtr(ptr);
    }
    ~UniquePtr() {
        delete(ptr);
    }
    int& operator*() {
        return *ptr;
    }
    UniquePtr(const UniquePtr& ptr) = delete;
    UniquePtr& operator=(const UniquePtr& ptr) = delete;
    UniquePtr(UniquePtr&& t) {
        ptr = t.ptr;
        t.ptr = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& t) {
        if (this != &t) {
            delete ptr;          // Release current resource
            ptr = t.ptr;     // Move ownership
            t.ptr = nullptr; // Reset the source
        }
        return *this;
    }
};

int main() {
    UniquePtr<int> ptr = UniquePtr<int>::make_unique( new int[100]);
    UniquePtr<int> ptr2 = UniquePtr<int>::make_unique(new int[100]);
    ptr2 = std::move(ptr);
    int value = *ptr2;
}
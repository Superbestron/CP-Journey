#include <algorithm>

template<typename T>
class shared_ptr {
public:
    constexpr shared_ptr() noexcept : ptr_(nullptr), count_(nullptr) {}
    // here we heap allocate so that multiple shared_ptr can reference the same ctr
    explicit shared_ptr(T* ptr) noexcept : ptr_(ptr) {
        if (ptr) count_= new std::size_t(1);
        else count_= nullptr;
    }

    shared_ptr(const shared_ptr& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
        if (count_) ++*count_;
    }

    shared_ptr& operator=(const shared_ptr& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_) ++*count_;
        }
        return *this;
    }

    shared_ptr(shared_ptr&& other) noexcept : ptr_(other.ptr_), count_(other.count_) {
        other.ptr_ = nullptr;
        other.count_ = nullptr;
    }

    shared_ptr& operator=(shared_ptr&& other) noexcept {
        if (this != &other) {
            release();
            ptr_ = other.ptr_;
            count_ = other.count_;
            other.ptr_ = nullptr;
            other.count_ = nullptr;
        }
        return *this;
    }

    ~shared_ptr() { release(); }

    T* get() const noexcept { return ptr_; }
    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    [[nodiscard]] std::size_t use_count() const noexcept { return count_ ? *count_ : 0; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

    void reset(T* ptr = nullptr) noexcept {
        release();
        if (ptr) {
            ptr_ = ptr;
            count_ = new std::size_t(1);
        }
    }

    void swap(shared_ptr& other) noexcept {
        std::swap(ptr_, other.ptr_);
        std::swap(count_, other.count_);
    }

    explicit shared_ptr(std::unique_ptr<T>&& uptr) noexcept : shared_ptr(uptr.release()) {}
private:
    void release() {
        if (count_) {
            if (--*count_ == 0) {
                delete ptr_;
                delete count_;
            }
        }
        ptr_ = nullptr;
        count_ = nullptr;
    }
    T* ptr_;
    std::size_t* count_;
};

template<typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

#include <utility>

template <typename T>
class unique_ptr {
 public:
  constexpr unique_ptr() noexcept : ptr_(nullptr) {}
  explicit unique_ptr(T* ptr) noexcept : ptr_(ptr) {}

  unique_ptr(const unique_ptr&) = delete;
  unique_ptr& operator=(const unique_ptr&) = delete;

  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.ptr_) {
      other.ptr_ = nullptr;
  }

  unique_ptr& operator=(unique_ptr&& other) noexcept {
    if (this != &other) {
      reset();
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~unique_ptr() { reset(); }

  T* get() const noexcept { return ptr_; }
  T& operator*() const noexcept { return *ptr_; }
  T* operator->() const noexcept { return ptr_; }
  explicit operator bool() const noexcept { return ptr_ != nullptr; }

  // Replace old ptr with new ptr
  void reset(T* ptr = nullptr) noexcept {
    if (ptr_ != ptr) {
      delete ptr_;
      ptr_ = ptr;
    }
  }

  // Gives up ownership of ptr
  T* release() noexcept {
    T* tmp = ptr_;
    ptr_ = nullptr;
    return tmp;
  }

  void swap(unique_ptr& other) noexcept {
    std::swap(ptr_, other.ptr_);
  }
 private:
  T* ptr_;
};

template<typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

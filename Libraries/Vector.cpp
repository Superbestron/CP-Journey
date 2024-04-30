#include <bits/stdc++.h>
using namespace std;

class Order {
 public:
  int* ptr;
  int a = 1, b = 2, c = 3;
  Order() : ptr(new int[10]) {
    for (int i = 0; i < 10; i++) {
      ptr[i] = i;
    }
    cout << "Calling Order default constructor!\n";
  }
  Order(int a, int b, int c) : a(a), b(b), c(c), ptr(new int[10]) {
    for (int i = 0; i < 10; i++) {
      ptr[i] = i;
    }
  }
  explicit Order(int x) : ptr(new int[10]) {
    for (int i = 0; i < 10; i++) {
      ptr[i] = i + x;
    }
  }
  Order(const Order& o) {
    a = o.a, b = o.b, c = o.c;
    ptr = new int[10];
    int* o_ptr = o.ptr;
    for (int i = 0; i < 10; i++) {
      ptr[i] = o_ptr[i];
    }
    cout << "Calling Order copy constructor!\n";
  }
  Order& operator=(const Order& o) {
    if (this != &o) {
      a = o.a, b = o.b, c = o.c;
      int* o_ptr = o.ptr;
      for (int i = 0; i < 10; i++) {
        ptr[i] = o_ptr[i];
      }
    }
    cout << "Calling Order copy assignment!\n";
    return *this;
  }
  Order(Order&& o) noexcept {
    delete [] ptr;
    ptr = o.ptr;
    a = o.a, b = o.b, c = o.c;
    o.ptr = nullptr;
    cout << "Calling Order move constructor!\n";
  }
  Order& operator=(Order&& o) noexcept {
    delete [] ptr;
    ptr = o.ptr;
    a = o.a, b = o.b, c = o.c;
    o.ptr = nullptr;
    cout << "Calling Order move assignment!\n";
    return *this;
  }
  [[nodiscard]] string toString() const {
    int* curr_ptr = ptr;
    string s;
    for (int i = 0; i < 10; i++) {
      s += to_string(*curr_ptr) + ' ';
      curr_ptr++;
    }
    return s;
  }
  ~Order() {
    delete [] ptr;
  }
};

template <typename T>
class V {
 public:
  T* ptr;
  size_t sz = 0;
  size_t capacity = 10;
  V() : ptr(new T[0]) {}
  explicit V(size_t size) : sz(size), ptr(new T[size]) {
    for (size_t i = 0; i < size; i++) {
      ptr[i] = T();
    }
  }
  V(size_t size, T& obj) : sz(size), ptr(new T[size]) {
    for (size_t i = 0; i < size; i++) {
      ptr[i] = obj;
    }
  }
  template<typename... Args>
  void emplace_back(Args&&... args) {
    if (sz < capacity) {
      cout << sz << '\n';
      ptr[sz++] = T(std::forward<Args>(args)...);
    } else {
      // Handle the case where the capacity is exceeded (e.g., resize the array).
      // You should implement this part based on your container's requirements.
    }
  }
  V(const V& o) : ptr(new T[o.sz]) {
    for (int i = 0; i < 10; i++) {
      ptr[i] = o.ptr[i];
    }
    cout << "Calling copy constructor!\n";
  }
  V& operator=(const V& v) {
    if (this != &v) {
      delete [] ptr;
      ptr = new T[v.sz];
      for (int i = 0; i < 10; i++) {
        ptr[i] = v.ptr[i];
      }
    }
    cout << "Calling copy assignment!\n";
    return *this;
  }
  V(T&& v) noexcept {
    delete [] ptr;
    ptr = v.ptr;
    v.ptr = nullptr;
    cout << "Calling move constructor!\n";
  }
  V& operator=(T&& v) noexcept {
    delete [] ptr;
    ptr = v.ptr;
    v.ptr = nullptr;
    cout << "Calling move assignment!\n";
    return *this;
  }
  ~V() {
    delete [] ptr;
  }
  T& operator[](int index) {
    if (index >= 0 && index < sz) {
      return ptr[index];
    } else {
      // Handle out-of-bounds access here
      throw std::out_of_range("Index out of bounds");
    }
  };
};

int main() {
  V<Order> v(5);
  cout << "\n\n";
  v.emplace_back(2, 3, 4);
  for (int i = 0; i < 6; i++) cout << v[i].a;
}

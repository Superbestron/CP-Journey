#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// A stack-based bounded ringbuffer

// A few optimisations:
// 1. Restrict size to powers of 2 so can do bitwise ops instead of expensive modulo
// 2. Padding and aligned push_ptr and pop_ptr to reduce false sharing
// 3. Cached/thread-local push_ptr and pop_ptr to reduce contention for SPSC

template <std::size_t N>
class RingBuffer {
  private:
    size_t push_ptr = 0; // always point to next write
    size_t pop_ptr = 0; // always point to oldest elem to read
    int arr[N + 1];
  public:
    bool push(int num) {
        size_t next_push_ptr = (push_ptr + 1) % (N + 1);
        if (next_push_ptr == pop_ptr) return false;
        arr[push_ptr] = num;
        push_ptr = next_push_ptr;
        return true;
    }
    void push_overwrite(int num) {
        if (push(num)) {
            return;
        }
        arr[push_ptr] = num;
        push_ptr = (push_ptr + 1) % (N + 1);
        pop_ptr = (pop_ptr + 1) % (N + 1);
    }
    int pop() {
        if (push_ptr == pop_ptr) return -1;
        int val = arr[pop_ptr];
        pop_ptr = (pop_ptr + 1) % (N + 1);
        return val;
    }
};

void test_empty_on_construction() {
    RingBuffer<4> rb;
    int val = rb.pop();
    // pop from empty should return -1 and size stays 0
    assert(val == -1);
}

void test_single_push_pop() {
    RingBuffer<4> rb;
    assert(rb.push(42));
    int val = rb.pop();
    assert(val == 42);
}

void test_fill_to_capacity() {
    RingBuffer<4> rb;

    assert(rb.push(1));
    assert(rb.push(2));
    assert(rb.push(3));
    assert(rb.push(4));  // buffer should now be full (size == N)

    // Next push should fail (buffer full)
    bool ok = rb.push(5);
    assert(!ok);

    // Pop all elements in FIFO order
    assert(rb.pop() == 1);
    assert(rb.pop() == 2);
    assert(rb.pop() == 3);
    assert(rb.pop() == 4);

    // Now empty again: pop should return -1
    assert(rb.pop() == -1);
}

void test_wrap_around_behavior() {
    RingBuffer<4> rb;

    // Fill partially
    assert(rb.push(10));
    assert(rb.push(20));
    assert(rb.push(30));

    // Pop one → makes room at the front
    assert(rb.pop() == 10);

    // Push more to cause wrap-around in push_ptr
    assert(rb.push(40));
    assert(rb.push(50));  // this should wrap push_ptr to 0 internally

    // Now order should be: 20, 30, 40, 50
    assert(rb.pop() == 20);
    assert(rb.pop() == 30);
    assert(rb.pop() == 40);
    assert(rb.pop() == 50);
}

void test_push_fail_does_not_change_state() {
    RingBuffer<2> rb;
    assert(rb.push(1));
    assert(rb.push(2));

    // Full now, next push should fail and not overwrite anything
    bool ok = rb.push(999);
    assert(!ok);

    // Values should be intact
    assert(rb.pop() == 1);
    assert(rb.pop() == 2);
}

int main() {
    test_empty_on_construction();
    test_single_push_pop();
    test_fill_to_capacity();
    test_wrap_around_behavior();
    test_push_fail_does_not_change_state();
}

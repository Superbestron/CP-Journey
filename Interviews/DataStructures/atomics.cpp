#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

/*
Example 1:
Input: n = 2
Output: "0102"
Explanation: There are three threads being fired asynchronously.
One of them calls zero(), the other calls even(), and the last one calls odd().
"0102" is the correct output.

Example 2:
Input: n = 5
Output: "0102030405"
 */

class ZeroEvenOdd {
  private:

  public:
    int n;
    atomic<int> curr = 0;
    atomic<bool> is_zero = true;
    ZeroEvenOdd(int n) {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        printNumber(0);
    }

    void even(function<void(int)> printNumber) {
        int num = curr.load(std::memory_order::seq_cst);
        printNumber(num);
    }

    void odd(function<void(int)> printNumber) {
        int num = curr.load(std::memory_order::seq_cst);
        printNumber(num);
    }
};

thread t1, t2, t3;

static void printNumber(int x) {
    cout << x << flush;
}

void thread1task(ZeroEvenOdd& obj) {
    while (true) {
        // time to print zero
        if (obj.is_zero.load(std::memory_order::seq_cst)) {
            obj.zero(printNumber);
            obj.curr.fetch_add(1, std::memory_order::seq_cst);
            obj.is_zero.store(false, std::memory_order::seq_cst); // let thread2 or thread 3 print
        }
        int num = obj.curr.load(std::memory_order::seq_cst);
        if (num == obj.n) break;
    }
}

void thread2task(ZeroEvenOdd& obj) {
    while (true) {
        bool to_print_zero = obj.is_zero.load(std::memory_order::seq_cst);
        if (to_print_zero) continue;
        int num = obj.curr.load(std::memory_order::seq_cst);
        if (num % 2 == 1) {
            obj.odd(printNumber);
            obj.is_zero.store(true, std::memory_order::seq_cst);
        }
        int num2 = obj.curr.load(std::memory_order::seq_cst);
        if (num2 == obj.n) break;
    }
}

void thread3task(ZeroEvenOdd& obj) {
    while (true) {
        bool to_print_zero = obj.is_zero.load(std::memory_order::seq_cst);
        if (to_print_zero) continue;
        int num = obj.curr.load(std::memory_order::seq_cst);
        if (num % 2 == 0) {
            obj.even(printNumber);
            obj.is_zero.store(true, std::memory_order::seq_cst);
        }
        int num2 = obj.curr.load(std::memory_order::seq_cst);
        if (num2 == obj.n) break;
    }
}

int main() {
    ZeroEvenOdd obj(5);
    thread t1(thread1task, std::ref(obj));
    thread t2(thread2task, std::ref(obj));
    thread t3(thread3task, std::ref(obj));

    t1.join();
    t2.join();
    t3.join();
}

#include <bits/stdc++.h>
using namespace std;

struct Data {
    priority_queue<int> max_heap; // first half
    priority_queue<int, vector<int>, greater<>> min_heap; // second half
    unordered_set<int> deleted;
    int max_heap_size = 0;
    int min_heap_size = 0;

    void insert(int x) {
        if (max_heap_size == 0) {
            max_heap.push(x);
            max_heap_size++;
            return;
        }
        if (max_heap_size == min_heap_size) {
            if (x <= min_heap.top()) {
                max_heap.push(x);
            } else {
                max_heap.push(min_heap.top());
                pop_min_heap();
                min_heap.push(x);
            }
            max_heap_size++;
        } else {
            if (x <= max_heap.top()) {
                min_heap.push(max_heap.top());
                pop_max_heap();
                max_heap.push(x);
            } else {
                min_heap.push(x);
            }
            min_heap_size++;
        }
    }

    void pop_min_heap() {
        min_heap.pop();
        while (!min_heap.empty() && deleted.contains(min_heap.top())) {
            deleted.erase(min_heap.top());
            min_heap.pop();
        }
    }

    void pop_max_heap() {
        max_heap.pop();
        while (!max_heap.empty() && deleted.contains(max_heap.top())) {
            deleted.erase(max_heap.top());
            max_heap.pop();
        }
    }

    [[nodiscard]] double get_median() const {
        if (max_heap_size == min_heap_size) return (max_heap.top() + min_heap.top()) / 2.0;
        else return max_heap.top();
    }

    // always called on non-empty
    void remove(int x) {
        deleted.insert(x);
        if (x > max_heap.top()) min_heap_size--;
        else max_heap_size--;
        // rebalance
        if (max_heap_size < min_heap_size) {
            max_heap.push(min_heap.top());
            pop_min_heap();
            max_heap_size++;
            min_heap_size--;
        }
    }
};

int main() {
    Data data{};
    vector<int> input = {1, 2, 3, 4, 5, 6};
    for (int i : input) data.insert(i);

    data.remove(2);
    cout << data.max_heap_size << '\n';
    cout << data.min_heap_size << '\n';
    cout << data.get_median() << '\n';
}

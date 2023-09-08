#include <iostream>
#include <map>
template<typename K, typename V>
class interval_map {
    friend void IntervalMapTest();
    V m_valBegin;
    std::map<K, V> m_map;
public:
    // constructor associates whole range of K with val
    explicit interval_map(V const& val) : m_valBegin(val)
    {}

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign(K const& keyBegin, K const& keyEnd, V const& val) {
        // INSERT YOUR SOLUTION HERE
        if (keyBegin >= keyEnd) return;
        auto it = m_map.lower_bound(keyBegin);
        if (it == m_map.end()) {
            m_map[keyEnd] = m_valBegin;
        } else {
            auto start = it;
            while (it != m_map.end() && it->first < keyEnd) {
                it++;
            }
            V curr_val = prev(it)->second;
            m_map.erase(start, it);
            m_map[keyEnd] = curr_val;
        }
        m_map[keyBegin] = val;
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin()) {
            return m_valBegin;
        } else {
            return (--it)->second;
        }
    }
};

void IntervalMapTest() {
    std::cout << "Test Case 1: Basic interval assignment\n";
    interval_map<int, char> map1('A');
    map1.assign(1, 4, 'B');
    // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'B', 3 -> 'B', 4 -> 'A
    for (int i = 0; i <= 4; ++i) {
        std::cout << i << " -> " << map1[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test Case 2: Overlapping intervals\n";
    interval_map<int, char> map2('A');
    map2.assign(1, 4, 'B');
    map2.assign(2, 5, 'C');
    // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'C', 3 -> 'C', 4 -> 'C', 5 -> 'A'
    for (int i = 0; i <= 5; ++i) {
        std::cout << i << " -> " << map2[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test Case 3: Non-consecutive keys\n";
    interval_map<int, char> map3('A');
    map3.assign(1, 4, 'B');
    map3.assign(6, 8, 'C');
    // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'B', 3 -> 'B', 4 -> 'A', 5 -> 'A', 6 -> 'C', 7 -> 'C', 8 -> 'A'
    for (int i = 0; i <= 8; ++i) {
        std::cout << i << " -> " << map3[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test Case 4: Edge case with empty interval\n";
    interval_map<int, char> map4('A');
    map4.assign(1, 1, 'B');
    // Expected mapping: 0 -> 'A', 1 -> 'A', 2 -> 'A'
    for (int i = 0; i <= 2; ++i) {
        std::cout << i << " -> " << map4[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test Case 5: Multiple Overlapping intervals\n";
    interval_map<int, char> map5('A');
    map5.assign(1, 4, 'B');
    map5.assign(4, 7, 'C');
    map5.assign(7, 10, 'D');
    map5.assign(2, 9, 'E');
    // Expected mapping: 0 -> 'A', 1 -> 'B', 2 - 8 -> 'E', 9 -> 'D', 10 -> 'A'
    for (int i = 0; i <= 10; ++i) {
        std::cout << i << " -> " << map5[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Test Case 6: Assigning value to a range with a positive key\n";
    interval_map<int, char> map6('A');
    map6.assign(-3, -1, 'B');
    // Expected mapping: -4 -> 'A', -3 -> 'B', -2 -> 'B', -1 -> 'A', 0 -> 'A'
    for (int i = -4; i <= 0; ++i) {
        std::cout << i << " -> " << map6[i] << std::endl;
    }
    std::cout << std::endl;
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

int main() {
    IntervalMapTest();
}
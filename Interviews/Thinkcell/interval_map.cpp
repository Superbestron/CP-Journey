/***
  interval_map<K, V> is a data structure that associates keys of type K with values of type V. It is designed to be
  used efficiently in situations where intervals of consecutive keys are associated with the same value. Your task is
  to implement the assign member function of this data structure, which is outlined below.

  interval_map<K, V> is implemented on top of std::map. For more information on std::map, you may refer to
  cppreference.com.

  Each key-value-pair (k, v) in interval_map<K, V>::m_map means that the value v is associated with all keys from k
  (including) to the next key (excluding) in m_map. The member interval_map<K,V>::m_valBegin holds the value that is
  associated with all keys less than the first key in m_map.

  Example: Let M be an instance of interval_map<int,char> where M.m_valBegin == 'A', M.m_map == {(1,'B'), (3,'A')},
  Then M represents the mapping
  ...
  -2 -> 'A'
  -1 -> 'A'
  0 -> 'A'
  1 -> 'B'
  2 -> 'B'
  3 -> 'A'
  4 -> 'A'
  5 -> 'A'
  ...

  The representation in the std::map must be canonical, that is, consecutive map entries must not contain the same
  value: ..., (3,'A'), (5,'A'), ... is not allowed. Likewise, the first entry in m_map must not contain the same value
  as m_valBegin. Initially, the whole range of K is associated with a given initial value, passed to the constructor of
  the interval_map<K, V> data structure.

  Key type K:
  - besides being copyable and assignable, is less-than comparable via operator<, and
  - does not implement any other operations, in particular no equality comparison or arithmetic operators.

  Value type V:
  - besides being copyable and assignable, is equality-comparable via operator==, and
  - does not implement any other operations.

  Your task is to implement the function assign. Your implementation is graded by the following criteria in this order:
  - Type requirements are met: You must adhere to the specification of the key and value type given above.
  - Correctness: Your program should produce a working interval_map with the behavior described above. In particular,
    pay attention to the validity of iterators. It is illegal to dereference end iterators. Consider using a checking
    STL implementation such as the one shipped with Visual C++ or GCC.
  - Canonicity: The representation in m_map must be canonical.
  - Running time: Imagine your implementation is part of a library, so it should be big-O optimal. In addition:
    - Do not make big-O more operations on K and V than necessary because you do not know how fast operations on K/V
      are; remember that constructions, destructions and assignments are operations as well.
    - Do not make more than one operation of amortized O(log N), in contrast to O(1), running time, where N is the
      number of elements in m_map.
    - Otherwise favor simplicity over minor speed improvements.

  You should not take longer than 9 hours, but you may of course be faster. Do not rush, we would not give you this
  assignment if it was trivial.

  When you are done, please complete the form and click Compile. You can improve and compile solutions as often as you
  like.

  Further instructions will be given once your code compiles correctly.
***/

#include <iostream>
#include <map>

template<typename T>
class Key : std::numeric_limits<T> {
 private:
  T v;

 public:
  explicit Key(T const &val) {
    v = val;
  }

  // copy constructor
  Key(const Key &other) : v(other.v) {}

  // copy assignment
  Key &operator=(const Key &other) {
    if (this != &other) {
      v = other.v;
    }
    return *this;
  }

  // overloaded < operator
  bool operator<(const Key &other) const {
    return v < other.v;
  }

//  friend std::ostream &operator<<(std::ostream &out, const Key<T> &c) {
//    out << c.v;
//    return out;
//  }
};

template<typename T>
class Value : std::numeric_limits<T> {
 private:
  T v;

 public:
  explicit Value(T const &val) {
    v = val;
  }

  // copy constructor
  Value(const Value &other) : v(other.v) {}

  // copy assignment
  Value &operator=(const Value &other) {
    if (this != &other) {
      v = other.v;
    }
    return *this;
  }

  // overloaded == operator
  bool operator==(const Value &d) const {
    return v == d.v;
  }

  // Disallow the inequality operator !=
  bool operator !=(const Value& other) = delete;

  friend std::ostream &operator<<(std::ostream &out, const Value<T> &c) {
    out << c.v;
    return out;
  }
};

template<typename K, typename V>
class interval_map {

 public:
  friend void IntervalMapTest();
  V m_valBegin;
  std::map<K, V> m_map;
  // constructor associates whole range of K with val
  explicit interval_map(V const &val) : m_valBegin(val) {}

  void clear(V const& val) {
    m_valBegin = val;
    m_map.clear();
  }

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  void assign(K const &keyBegin, K const &keyEnd, V const &val) {
    // INSERT YOUR SOLUTION HERE
    if (!(keyBegin < keyEnd))
      return;

    // if inserting into range of the same value before, don't insert
    // if the value existing already after out pointer, erase it
    auto before_begin_bound = m_map.lower_bound(keyBegin);
    if (before_begin_bound != m_map.begin()) {
      --before_begin_bound;
    }
    auto insert_res = before_begin_bound->second == val ?
                      before_begin_bound : m_map.insert_or_assign(before_begin_bound, keyBegin, val);

    auto end_interval = m_map.lower_bound(keyEnd);

    if (end_interval != m_map.end() && end_interval->second == val)
      end_interval++;

    insert_res++;
    m_map.erase(insert_res, end_interval);

    if (end_interval == m_map.end())
      this->assign(keyEnd, std::numeric_limits<K>::max(), before_begin_bound->second);
    else
      this->assign(keyEnd, end_interval->first, before_begin_bound->second);

  }

  // look-up of the value associated with key
  V const &operator[](K const &key) const {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }
};

void runIntervalMapTest() {

  std::srand(time(0));

  // Number of random test cases
  const int numTestCases = 1000;
  // Generate random test cases
  for (int i = 0; i < numTestCases; ++i) {

    interval_map<int, char> iMap('F');
    std::map<int, char> referenceMap;
    for (int key = 0; key <= 30; ++key) {
      referenceMap[key] = 'F';
    }

    int segments = 0;
    for (int j = 0; j < 5; j++) {
      // Randomly generate startKey, endKey, and value
      int startKey = std::rand() % 30;
      int endKey = startKey + std::rand() % (30 - startKey);
      char value = static_cast<char>('A' + std::rand() % 26);

      // Perform the assignment in both the inter_map and referenceMap
      iMap.assign(startKey, endKey, value);
//      std::cout << startKey << ' ' << endKey << ' ' << value << '\n';
      for (int key = startKey; key < endKey; ++key) {
        referenceMap[key] = value;
      }
    }
    char prev = 'F';
    for (int key = 0; key <= 30; ++key) {
      char value = referenceMap[key];
      if (value != prev) segments++;
      prev = value;
    }

    // Compare the results of inter_map with the referenceMap
    // and print an error message if they differ
    for (const auto& entry : referenceMap) {
      int key = entry.first;
      char expectedValue = entry.second;
      char actualValue = iMap[key]; // You may need a getValue() function in your inter_map class
      if (actualValue != expectedValue) {
        std::cout << "Test "<<i <<" failed: Key " << key << ", Expected " << expectedValue << ", Actual " << actualValue << std::endl;
        assert(false);
      }
    }
    if (segments != (int) iMap.m_map.size()) {
      std::cout << "Test "<<i <<" failed: Expected " << segments << ", Actual " << iMap.m_map.size() << std::endl;
      assert(false);
    }
  }
  std::cout << "Randomized test completed." << std::endl;
}

void IntervalMapTest() {
//  std::map<Key<int>, char> myMap;
//  myMap[14] = MyClass(42);
  Value initial('a');
  interval_map<Key<int>, Value<char>> imap {initial};
  Key st(10), ed(20);
  Value next('b');
  imap.assign(st, ed, next);

  Key k1(1), k2(2);
  Value v1('A'), v2('B');

//  k1==k2; // Error
//  v1==v2;
//  v1<v2; // Error
//  v1>v2; // Error
//  v1!=v2; // Error
//  k1<k2;
//  k1>k2; // Error
//  k1!=k2; // Error
//  k1=k2;
//  v1=v2;

  // All Errors
//  k1++;
//  k1--;
//  k1+k2;
//  k1-k2;
//  k1*k2;
//  k1/k2;
//  k1%k2;
//  k1+=k2;
//  k1+=5;
//  k1-=k2;
//  k1*=k2;
//  k1/=k2;
//  k1<<k2;
//  k1>>k2;
//  k1<<2;
//  v1+v2;
//  v1-v2;
//  v1*v2;
//  v1/v2;
//  v1%v2;
//  v1++;
//  v1--;
//  v1+=v2;
//  v1-=v2;
//  v1*=v2;
//  v1/=v2;

  std::cout << "Test Case 1: Basic interval assignment\n";
  interval_map<int, char> map1('A');
  map1.assign(1, 4, 'B');
  // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'B', 3 -> 'B', 4 -> 'A
  std::string ans {"ABBBA"};
  for (int i = 0; i <= 4; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
    assert(map1[i] == ans[i]);
  }
  std::cout << std::endl;

  std::cout << "Test Case 2: Overlapping intervals\n";
  interval_map<int, char> map2('A');
  map2.assign(1, 4, 'B');
  map2.assign(2, 5, 'C');
  ans = "ABCCCA";
  // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'C', 3 -> 'C', 4 -> 'C', 5 -> 'A'
  for (int i = 0; i <= 5; ++i) {
    std::cout << i << " -> " << map2[i] << std::endl;
    assert(map2[i] == ans[i]);
  }
  std::cout << std::endl;

  std::cout << "Test Case 3: Non-consecutive keys\n";
  interval_map<int, char> map3('A');
  map3.assign(1, 4, 'B');
  map3.assign(6, 8, 'C');
  ans = "ABBBAACCA";
  // Expected mapping: 0 -> 'A', 1 -> 'B', 2 -> 'B', 3 -> 'B', 4 -> 'A', 5 -> 'A', 6 -> 'C', 7 -> 'C', 8 -> 'A'
  for (int i = 0; i <= 8; ++i) {
    std::cout << i << " -> " << map3[i] << std::endl;
    assert(map3[i] == ans[i]);
  }
  std::cout << std::endl;

  std::cout << "Test Case 4: Edge case with empty interval\n";
  interval_map<int, char> map4('A');
  map4.assign(1, 1, 'B');
  ans = "AAA";
  // Expected mapping: 0 -> 'A', 1 -> 'A', 2 -> 'A'
  for (int i = 0; i <= 2; ++i) {
    std::cout << i << " -> " << map4[i] << std::endl;
    assert(map4[i] == ans[i]);
  }
  std::cout << std::endl;

  std::cout << "Test Case 5: Multiple Overlapping intervals\n";
  interval_map<int, char> map5('A');
  map5.assign(1, 4, 'B');
  map5.assign(4, 7, 'C');
  map5.assign(7, 10, 'D');
  map5.assign(2, 9, 'E');
  ans = "ABEEEEEEEDA";
  // Expected mapping: 0 -> 'A', 1 -> 'B', 2 - 8 -> 'E', 9 -> 'D', 10 -> 'A'
  for (int i = 0; i <= 10; ++i) {
    std::cout << i << " -> " << map5[i] << std::endl;
    assert(map5[i] == ans[i]);
  }
  std::cout << std::endl;

  std::cout << "Test Case 6: Assigning value to a range with a positive key\n";
  interval_map<int, char> map6('A');
  map6.assign(-3, -1, 'B');
  // Expected mapping: -4 -> 'A', -3 -> 'B', -2 -> 'B', -1 -> 'A', 0 -> 'A'
  ans = "ABBAA";
  for (int i = -4; i <= 0; ++i) {
    std::cout << i << " -> " << map6[i] << std::endl;
    assert(map6[i] == ans[i + 4]);
  }
  std::cout << std::endl;

  map1.clear('A');
  map1.assign(1, 2, 'B');
  ans = "ABA";
  for (int i = 0; i <= 2; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
    assert(map1[i] == ans[i]);
  }
  assert(map1.m_map.size() == 2);
  std::cout << std::endl;

  map1.clear('A');
  map1.assign(1, 3, 'B');
  map1.assign(6, 10, 'B');
  map1.assign(3, 6, 'B');
  for (int i = 0; i <= 10; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
  }
  std::cout << map1.m_map.size() << '\n';
  std::cout << std::endl;

  map1.clear('F');
  map1.assign(1, 24, 'D');
  map1.assign(9, 27, 'X');
  map1.assign(1, 15, 'B');
  map1.assign(18, 27, 'F');
  map1.assign(23, 28, 'F');
  for (int i = 0; i < 30; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
  }
  std::cout << map1.m_map.size() << '\n';
  std::cout << std::endl;

  map1.clear('F');
  map1.assign(11, 29, 'O');
  map1.assign(6, 25, 'Q');
  map1.assign(10, 19, 'O');
  map1.assign(14, 23, 'N');
  map1.assign(20, 23, 'H');
  for (int i = 0; i < 30; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
  }
  std::cout << map1.m_map.size() << '\n';
  std::cout << std::endl;

  map1.clear('F');
  map1.assign(20, 27, 'R');
  map1.assign(16, 27, 'A');
  map1.assign(20, 25, 'I');
  map1.assign(25, 28, 'Y');
  map1.assign(3, 21, 'F');
  for (int i = 0; i < 30; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
  }
  std::cout << map1.m_map.size() << '\n';
  std::cout << std::endl;

  map1.clear('F');
  map1.assign(7, 29, 'B');
  map1.assign(6, 17, 'S');
  map1.assign(2, 11, 'B');
  map1.assign(17, 25, 'S');
  map1.assign(17, 17, 'X');
  for (int i = 0; i < 30; ++i) {
    std::cout << i << " -> " << map1[i] << std::endl;
  }
  assert(map1.m_map.size() == 4);
  std::cout << std::endl;
}

// Many solutions we receive are incorrect. Consider using a randomized test.txt
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test.txt function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

int main() {
//  IntervalMapTest();
  runIntervalMapTest();
}

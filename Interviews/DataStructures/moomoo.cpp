#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Given an integer array nums, find all elements in the array that meet the following conditions:
//
// The element is strictly greater than all elements to its left;
// The element is strictly smaller than all elements to its right.

// There are two tables below: the user table (user table) and the thread table (post table).
// Assume there are 1 million users and 5 million posts. Write a SQL statement to display the names and post counts
// of the top 10 users who have posted the most, and specify the reasonable index fields to design for this statement.
// Additionally, explain how to confirm which index your written SQL will use, and state whether your SQL is the
// optimal solution.
// user table：user_id, username, password, create_time
// thread table： thread_id, user_id, title, content, create_time

// SELECT u.username, COUNT(*) AS post_count FROM thread t
// JOIN user u ON u.user_id = t.user_id
// GROUP BY t.user_id, u.username
// ORDER BY post_count DESC
// LIMIT 10;

// There are 25 horses and 5 race tracks. What is the minimum number of races required to find out the top 3 horses?
// 1. 5 races for 25 horses
// 2. Race the 5 winners, left with A1, A2, A3, B1, B2, C1
// 3. Race the last 5, pick the top 2

template <auto T>
using deleter_fn = std::integral_constant<std::decay_t<decltype(T)>, T>;

template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    constexpr operator T() const noexcept { return value; }
    constexpr T operator()() const noexcept { return value; }
};

template<typename T>
T const* mini(T const* a, T const* b) {
    return (a < b) ? a : b;
}

template<>
char const* mini(char const* pa, char const* pb) {
    return (strcmp(pa, pb) < 0) ? pa : pb;
}


int main() {
    vector<int> input = {1, 2, 8, 4, 3, 9, 10};
    int n = input.size();
    vector<bool> biggest_seen_so_far(n);
    vector<bool> smallest_seen_so_far(n);
    vector<int> ans;
    int max_num = -1e9;
    for (int i = 0; i < n; i++) {
        if (input[i] > max_num) {
            biggest_seen_so_far[i] = true;
        } else {
            biggest_seen_so_far[i] = false;
        }
        max_num = max(max_num, input[i]);
    }
    int min_num = 1e9;
    for (int i = n - 1; i >= 0; i--) {
        if (input[i] < min_num) {
            smallest_seen_so_far[i] = true;
        } else {
            smallest_seen_so_far[i] = false;
        }
        min_num = min(min_num, input[i]);
    }
    for (int i = 0; i < n; i++) {
        if (biggest_seen_so_far[i] && smallest_seen_so_far[i]) {
            ans.push_back(input[i]);
        }
    }
    for (auto& i : ans) {
        cout << i << ' ';
    }
}

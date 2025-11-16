#include <bits/stdc++.h>
using namespace std;

int solution(string files) {
    // Write solution here
    unordered_map<char, int> map;
    for (char c : files) {
        if (map.count(c) == 0) map[c] = 1;
        else map[c]++;
    }
    int ans = 0;
    bool odd = false;
    for (auto const& [key, val] : map) {
        if ((val & 0b1) == 0) ans += val;
        else {
            odd = true;
            ans += val - 1;
        }
    }
    if (odd) return ans + 1;
    return ans;
}

int main() {
    string files;
    cin >> files;
    cout << solution(files) << '\n';
}

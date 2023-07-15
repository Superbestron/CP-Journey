#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, t, c;
    cin >> n >> t;
    vector<int> v;
    while (n-- > 0) {
        cin >> c;
        v.push_back(c);
    }

    if (t == 1) {
        // 2 sum problem
        unordered_set<int> m;
        for (int i : v) {
            if (m.count(7777 - i) == 1) {
                cout << "Yes";
                return 0;
            }
            m.insert(i);
        }
        cout << "No";
    } else if (t == 2) {
        unordered_set<int> m;
        for (int i : v) {
            if (m.count(i) == 1) {
                cout << "Contains duplicate";
                return 0;
            }
            m.insert(i);
        }
        cout << "Unique";
    } else if (t == 3) {
        unordered_map<int, int> m;
        for (int i : v) {
            m[i]++;
        }
        for (auto& p : m) {
            if (2 * p.second > v.size()) {
                cout << p.first;
                return 0;
            }
        }
        cout << -1;
    } else if (t == 4) {
        sort(v.begin(), v.end());
        if (v.size() % 2 == 0) {
            cout << v[v.size() / 2 - 1] << ' ' << v[v.size() / 2];
        } else {
            cout << v[v.size() / 2];
        }
    } else {
        sort(v.begin(), v.end());
        for (int i : v) {
            if (i > 999) break;
            if (i >= 100) {
                cout << i << ' ';
            }
        }
    }
}

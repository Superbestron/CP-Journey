#include <bits/stdc++.h>

// Unfinished

using namespace std;

int* a;
int* b;
int n;
unordered_set<int> s;

long long backtrack(int index) {
    if (index == n) {
        return 1;
    }
    long long ans = 0;
    long long temp = 0;
    if (s.count(a[index])) {
        s.erase(a[index]);
        temp = backtrack(index + 1);
        s.insert(a[index]);
    }
    if (a[index] == b[index]) {
        ans += n * temp;
    } else {
        ans += temp;
        if (s.count(b[index])) {
            s.erase(b[index]);
            ans += backtrack(index + 1);
            s.insert(b[index]);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        a = new int[n], b = new int[n];
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            s.insert(i + 1);
        }
        cout << backtrack(0) % 998244353 << endl;
    }
}
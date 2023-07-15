#include <iostream>
#include <vector>

using namespace std;

// Literal simulation of the shuffle
// Be careful of the corner case where inshuffle and outshuffle works differently for odd numbers of cards

void inshuffle(vector<int>& v) {
    int mid = v.size() / 2;
    vector<int> v1, v2;
    for (int i = 0; i < v.size(); i++) {
        if (i < mid) v1.push_back(v[i]);
        else v2.push_back(v[i]);
    }
    v.clear();
    int mini_size = min(v1.size(), v2.size());
    for (int i = 0; i < mini_size; i++) {
        v.push_back(v2[i]);
        v.push_back(v1[i]);
    }
    if (v1.size() > mini_size) v.push_back(v1.back());
}

void outshuffle(vector<int>& v) {
    int mid = (v.size() + 1) / 2;
    vector<int> v1, v2;
    for (int i = 0; i < v.size(); i++) {
        if (i < mid) v1.push_back(v[i]);
        else v2.push_back(v[i]);
    }
    v.clear();
    int mini_size = min(v1.size(), v2.size());
    for (int i = 0; i < mini_size; i++) {
        v.push_back(v1[i]);
        v.push_back(v2[i]);
    }
    if (v1.size() > mini_size) v.push_back(v1.back());
}

bool solved(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != i) return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, ans = 0; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) v[i] = i;
    string s; cin >> s;
    bool in = (s == "in");
    while(true) {
        ans++;
        if (in) inshuffle(v);
        else outshuffle(v);
        if (solved(v)) break;
    }
    cout << ans << endl;
}
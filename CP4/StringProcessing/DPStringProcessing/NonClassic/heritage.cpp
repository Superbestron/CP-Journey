#include <bits/stdc++.h>

using namespace std;

long long arr[33][33];
int b[32], N;
string T, cur;
unordered_map<int, unordered_map<int, int>> AL;
const long long MOD = 1e9 + 7;

long long dp(int i, int j) {
    long long& ans = arr[i][j];
    if (ans != -1) return ans;
    ans = 0;
    if (AL[i].count(j)) ans = AL[i][j];
    for (int c = i + 1; c < j; c++) {
        if (AL[i].count(c)) ans = ans + AL[i][c] * dp(c, j) % MOD;
    }
    ans %= MOD;
    return ans;
}

void kmpPreprocess(string& P) { // call this first
    int i = 0, j = -1; b[0] = -1; // starting values
    while (i < P.size()) { // pre-process P
        while ((j >= 0) && (P[i] != P[j])) j = b[j]; // different, reset j
        ++i; ++j; // same, advance both
        b[i] = j;
    }
}

void kmpSearch(string& P, int val) { // similar as above
    int i = 0, j = 0; // starting values
    while (i < T.size()) { // search through T
        while ((j >= 0) && (T[i] != P[j])) j = b[j]; // if different, reset j
        ++i; ++j; // if same, advance both
        if (j == P.size()) { // a match is found
            AL[i - j][i - j + P.size()] = val;
            j = b[j]; // prepare j for the next
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> T;
    memset(arr, -1, sizeof arr);
    for (int i = 0; i < N; i++) {
        int val;
        cin >> cur >> val;
        kmpPreprocess(cur);
        kmpSearch(cur, val);
    }
    cout << dp(0, T.size());
}
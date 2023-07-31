#include <bits/stdc++.h>

using namespace std;

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 31 + v.second;
    }
};

unordered_set<pair<int, int>, pair_hash> s;

//  Use 2 hashes to avoid collisions

// Rabin-Karp's algorithm specific code
typedef long long ll;

const int p1 = 131;                               // p and M are
const int M1 = 1e9+7;                             // relatively prime
const int p2 = 997;                               // p and M are
const int M2 = 1e9+7;                             // relatively prime

int Pow1[100000];                                  // to store p^i % M
int Pow2[100000];                                    // to store prefix hashes
int cnt = 0;

// Parsing can be optimised but I was too lazy
pair<int, int> parse(int l, int r, string& T, bool is_first) {
    if (T[l] != '(') {
        int num = stoi(T.substr(l, r + 1));
        num--;
        pair<int, int> hash = make_pair(Pow1[num], Pow2[num]);
        if (is_first) s.insert(hash);
        else if (s.count(hash)) cnt++;
        return hash;
    }
    int l_b = 1, mid = -1;
    for (int i = l + 1; l <= r; i++) {
        if (T[i] == '(') l_b++;
        else if (T[i] == ')') l_b--;
        if (l_b == 1 && T[i] == ',') {
            mid = i;
            break;
        }
    }
    pair<int, int> a = parse(l + 1, mid - 1, T, is_first);
    pair<int, int> b = parse(mid + 1, r - 1, T, is_first);
    pair<int, int> hash = make_pair(a.first + b.first, a.second + b.second);
    if (is_first) s.insert(hash);
    else if (s.count(hash)) cnt++;
    return hash;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    string A, B;
    cin >> A >> B;
    Pow1[0] = 1, Pow2[0] = 1;                                    // compute p^i % M
    for (int i = 1; i < N; ++i) {                  // O(n)
        Pow1[i] = ((ll) Pow1[i - 1] * p1) % M1;
        Pow2[i] = ((ll) Pow2[i - 1] * p2) % M2;
    }
    parse(0, A.size() - 1, A, true);
    parse(0, B.size() - 1, B, false);
    cout << cnt;
}
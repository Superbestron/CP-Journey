#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

vi match, vis;
vector<vi> AL;

int Aug(int L) {
    if (vis[L]) return 0;
    vis[L] = 1;
    for (auto& R : AL[L]) {
        if ((match[R] == -1) || Aug(match[R])) {
            match[R] = L;
            return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int B, G, N;
    cin >> B >> G;
    string name, book_name;
    unordered_map<string, int> read_by;
    for (int i = 0; i < B; i++) {
        cin >> name >> N;
        for (int j = 0; j < N; j++) {
            cin >> book_name;
            read_by[book_name] = i;
        }
    }
    int V = B + G, VLeft = B;
    AL.assign(V, {});
    for (int i = 0; i < G; i++) {
        cin >> name >> N;
        for (int j = 0; j < N; j++) {
            cin >> book_name;
            AL[read_by[book_name]].push_back(B + i);
        }
    }

    match.assign(V, -1);
    int MCBM = 0;
    for (int L = 0; L < B; L++) {
        vis.assign(VLeft, 0);
        MCBM += Aug(L);
    }
    cout << MCBM << '\n';
}
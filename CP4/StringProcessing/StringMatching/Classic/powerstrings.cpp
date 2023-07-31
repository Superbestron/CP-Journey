#include <bits/stdc++.h>

using namespace std;

int b[2000000], ans;
string T, P;

void kmpPreprocess() { // call this first
    int i = 0, j = -1; b[0] = -1; // starting values
    while (i < P.size()) { // pre-process P
        while ((j >= 0) && (P[i] != P[j])) j = b[j]; // different, reset j
        ++i; ++j; // same, advance both
        b[i] = j;
    }
}

void kmpSearch() { // similar as above
    int i = 0, j = 0; // starting values
    while (i < T.size()) { // search through T
        while ((j >= 0) && (T[i] != P[j])) j = b[j]; // if different, reset j
        ++i; ++j; // if same, advance both
        if (j == P.size()) { // a match is found
            ans++;
            j = b[j]; // prepare j for the next
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (getline(cin, P) && P != ".") {
        T = P + P;
        ans = 0;
        kmpPreprocess();
        kmpSearch();
        cout << ans - 1 << '\n';
    }
}
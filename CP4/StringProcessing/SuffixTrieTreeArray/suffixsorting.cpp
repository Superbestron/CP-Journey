#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SuffixArray {
private:
    vi RA;                                         // rank array

    void countingSort(int k) {                     // O(n)
        int maxi = max(300, n);                      // up to 255 ASCII chars
        vi c(maxi, 0);                               // clear frequency table
        for (int i = 0; i < n; ++i)                  // count the frequency
            ++c[i+k < n ? RA[i+k] : 0];                // of each integer rank
        for (int i = 0, sum = 0; i < maxi; ++i) {
            int t = c[i]; c[i] = sum; sum += t;
        }
        vi tempSA(n);
        for (int i = 0; i < n; ++i)                  // sort SA
            tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
        swap(SA, tempSA);                            // update SA
    }

    void constructSA() {                           // can go up to 400K chars
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0);               // the initial SA
        RA.resize(n);
        for (int i = 0; i < n; ++i) RA[i] = T[i];    // initial rankings
        for (int k = 1; k < n; k <<= 1) {            // repeat log_2 n times
            // this is actually radix sort
            countingSort(k);                           // sort by 2nd item
            countingSort(0);                           // stable-sort by 1st item
            vi tempRA(n);
            int r = 0;
            tempRA[SA[0]] = r;                         // re-ranking process
            for (int i = 1; i < n; ++i)                // compare adj suffixes
                tempRA[SA[i]] = // same pair => same rank r; otherwise, increase r
                        ((RA[SA[i]] == RA[SA[i-1]]) && (RA[SA[i]+k] == RA[SA[i-1]+k])) ?
                        r : ++r;
            swap(RA, tempRA);                          // update RA
            if (RA[SA[n-1]] == n-1) break;             // nice optimization
        }
    }

public:
    const char* T;                                 // the input string
    const int n;                                   // the length of T
    vi SA;                                         // Suffix Array

    SuffixArray(const char* initialT, const int _n) : T(initialT), n(_n) {
        constructSA();                               // O(n log n)
    }
};

// including null-terminated string
const int MAX_N = 100001;                        // can go up to 450K chars

char T[MAX_N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    while (cin.getline(T, MAX_N)) {
        int n, idx;
        cin >> n;
        int sz = (int) strlen(T);
        T[sz++] = char(9);
        SuffixArray S(T, sz);
        for (int i = 0; i < n; i++) {
            cin >> idx;
            cout << S.SA[idx + 1] << ' ';
        }
        cout << '\n';
        cin.ignore();
        memset(T, 0, sizeof T);
    }
}

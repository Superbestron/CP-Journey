#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

class SuffixArray {
private:
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

    void computeLCP() {
        vi Phi(n);
        vi PLCP(n);
        PLCP.resize(n);
        Phi[SA[0]] = -1;                             // default value
        for (int i = 1; i < n; ++i)                  // compute Phi in O(n)
            Phi[SA[i]] = SA[i-1];                      // remember prev suffix
        for (int i = 0, L = 0; i < n; ++i) {         // compute PLCP in O(n)
            if (Phi[i] == -1) { PLCP[i] = 0; continue; } // special case
            while ((i+L < n) && (Phi[i]+L < n) && (T[i+L] == T[Phi[i]+L]))
                ++L;                                     // L incr max n times
            PLCP[i] = L;
            L = max(L-1, 0);                           // L dec max n times
        }
        LCP.resize(n);
        for (int i = 0; i < n; ++i)                  // compute LCP in O(n)
            LCP[i] = PLCP[SA[i]];                      // restore PLCP
    }

public:
    const char* T;                                 // the input string
    const int n;                                   // the length of T
    vi SA;                                         // Suffix Array
    vi LCP;                                        // of adj sorted suffixes
    vi RA;                                         // rank array

    SuffixArray(const char* initialT, const int _n) : T(initialT), n(_n) {
        constructSA();                               // O(n log n)
        computeLCP();                                // O(n)
    }
};

const int MAX_N = 100010;
char T[MAX_N];

class SparseTable {
private:
    vector<vi> SpT;
    int N, K;
public:
    SparseTable(vi& initialA) {
        N = initialA.size();
        K = MSB(N);

        SpT.resize(K);
        SpT[0] = initialA;

        for (int i = 1; i < K; i++) {
            for (int j = 0; j + (1 << i) - 1 < N; j++) {
                int x = SpT[i - 1][j];
                int y = SpT[i - 1][j + (1 << (i - 1))];
                SpT[i].push_back(min(x, y));
            }
        }
    }

    inline int MSB(unsigned int x) { return 32 - __builtin_clz(x); }

    int RMQ(int i, int j) {
        int k = MSB(j - i + 1) - 1;
        int x = SpT[k][i];
        int y = SpT[k][j - (1 << k) + 1];
        return min(x, y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, i, j, l, r;
    cin.getline(T, MAX_N);
    int n = (int) strlen(T);
    T[n++] = '$';
    SuffixArray S(T, n);
    SparseTable SpT(S.LCP);
    cin >> q;
    while (q--) {
        cin >> i >> j;
        l = min(S.RA[i], S.RA[j]);
        r = max(S.RA[i], S.RA[j]);
        // l + 1 instead of l because LCP[i] by construction
        // already compares the current suffix with the previous suffix
        cout << SpT.RMQ(l + 1, r) << '\n';
    }
}
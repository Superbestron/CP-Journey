#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

vi A, p; //  predecessor array
void print_LIS(int i) {  // backtracking routine
  if (p[i] == -1) {
    cout << A[i] << ' ';
    return;
  }  // base case
  print_LIS(p[i]); // backtrack
  cout << A[i] << ' ';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  while (cin >> n) {
    A.assign(n, 0);
    for (int &i : A) cin >> i;
    int k = 0, lis_end = 0;
    vi L(n, 0), L_id(n, 0);
    p.assign(n, -1);
    for (int i = 0; i < n; ++i) { // O(n log k)
      int pos = lower_bound(L.begin(), L.begin() + k, A[i]) - L.begin();
      L[pos] = A[i]; // greedily overwrite this
      L_id[pos] = i; // remember the index too
      p[i] = pos ? L_id[pos - 1] : -1; // predecessor info
      if (pos == k) { // can extend LIS?
        k = pos + 1; // k = longer LIS by +1
        lis_end = i; // keep best ending i
      }
    }
    cout << k << '\n';
    print_LIS(lis_end);
    cout << '\n';
  }
}

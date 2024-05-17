#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

int t, n, m;

int findIndexOfMinInversion(int item, vi& b, int st, int et) {
  int ctr = 0, best = 0, pos = st;
  for (int i = st; i <= et; i++) {
    if (item < b[i]) {
      ctr--;
    } else {
      ctr++;
    }
    if (ctr >= best) {
      ctr = best;
      pos = i + 1;
    }
  }
  return pos;
}

void binaryInsert(vi& a, int sa, int ea, vi& b, int sb, int eb, vi& i) {
  if (sa > ea) {
    return;
  }
  int ma = (sa + ea) / 2;
  int mb = findIndexOfMinInversion(a.at(ma), b, sb, eb);
  i.at(ma) = mb;
  binaryInsert(a, sa, ma - 1, b, sb, mb - 1, i);
  binaryInsert(a, ma + 1, ea, b, mb - 1, eb, i);
}

int merge(vi &arr, vi &temp, int left, int mid, int right) {
  int i = left, j = mid, k = left, inv_count = 0;
  while ((i <= mid - 1) && (j <= right)) {
    if (arr.at(i) <= arr.at(j)) {
      temp.at(k++) = arr.at(i++);
    }
    else {
      temp.at(k++) = arr.at(j++);
      inv_count = inv_count + (mid - i);
    }
  }

  while (i <= mid - 1)
    temp.at(k++) = arr.at(i++);

  while (j <= right)
    temp.at(k++) = arr.at(j++);

  for (i = left; i <= right; i++)
    arr.at(i) = temp.at(i);

  return inv_count;
}

int mergeSort(vi &arr, vi &temp, int left, int right) {
  int mid, inv_count = 0;
  if (right > left) {
    mid = (right + left) / 2;

    inv_count += mergeSort(arr, temp, left, mid);
    inv_count += mergeSort(arr, temp, mid + 1, right);
    inv_count += merge(arr, temp, left, mid + 1, right);
  }
  return inv_count;
}

inline void solve() {
  cin >> n >> m;
  vi a(n), b(m);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  vi i(m), merged;
  sort(b.begin(), b.end());
  binaryInsert(b, 0, m - 1, a, 0, n - 1, i);
  int aCtr = 0;
  for (int iCtr = 0; iCtr < m; iCtr++) {
    int curr = i.at(iCtr);
    while (aCtr < curr) {
      merged.push_back(a.at(aCtr++));
    }
    merged.push_back(b.at(iCtr));
  }

  vi temp(merged.size());
  cout << mergeSort(merged, temp, 0, merged.size() - 1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(false); // speed up reading input
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    solve();
  }
}

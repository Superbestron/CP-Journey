#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<ii> vii;
const int INF = 1e9;

struct Node {
  // max sum subarray
  int first;
  int second;
};

Node max_combine(Node left, Node right) {
  if (left.first >= right.first) {
    if (left.second >= right.first) return left;
    else return {left.first, right.first};
  }
  if (left.first >= right.second) return {right.first, left.first};
  return right;
}

Node min_combine(Node left, Node right) {
  if (left.first <= right.first) {
    if (left.second <= right.first) return left;
    else return {left.first, right.first};
  }
  if (left.first <= right.second) return {right.first, left.first};
  return right;
}

class MinSegmentTree {
 private:
  Node build(vi &arr, int idx, int l, int r) {
    if (l == r) return st[idx] = {arr[l], INF};  // leaf node
    int mid = (l + r) / 2;
    Node left = build(arr, 2 * idx, l, mid);
    Node right = build(arr, 2 * idx + 1, mid + 1, r);
    return st[idx] = min_combine(left, right);
  }
  Node query(int l, int r, int idx, int node_l, int node_r) {
    if (l > node_r || r < node_l) return {INF, INF};  // out of range
    if (l <= node_l && r >= node_r) return st[idx];  // in range
    int mid = (node_l + node_r) / 2;
    Node left = query(l, r, 2 * idx, node_l, mid);
    Node right = query(l, r, 2 * idx + 1, mid + 1, node_r);
    return min_combine(left, right);
  }

 public:
  int n;
  vector<Node> st;
  MinSegmentTree(vi &arr) : n(arr.size()), st(4 * n) {
    build(arr, 1, 0, n - 1);
  }
  Node query(int l, int r) {
    return query(l, r, 1, 0, n - 1);
  }
};

class MaxSegmentTree {
 private:
  Node build(vi &arr, int idx, int l, int r) {
    if (l == r) return st[idx] = {arr[l], -INF};  // leaf node
    int mid = (l + r) / 2;
    Node left = build(arr, 2 * idx, l, mid);
    Node right = build(arr, 2 * idx + 1, mid + 1, r);
    return st[idx] = max_combine(left, right);
  }
  Node query(int l, int r, int idx, int node_l, int node_r) {
    if (l > node_r || r < node_l) return {-INF, -INF};  // out of range
    if (l <= node_l && r >= node_r) return st[idx];  // in range
    int mid = (node_l + node_r) / 2;
    Node left = query(l, r, 2 * idx, node_l, mid);
    Node right = query(l, r, 2 * idx + 1, mid + 1, node_r);
    return max_combine(left, right);
  }

 public:
  int n;
  vector<Node> st;
  MaxSegmentTree(vi &arr) : n(arr.size()), st(4 * n) {
    build(arr, 1, 0, n - 1);
  }
  Node query(int l, int r) {
    return query(l, r, 1, 0, n - 1);
  }
};

void solve() {
  int n, Q; cin >> n >> Q;
  vi A(n);
  for (int &i : A) cin >> i;
  MaxSegmentTree l(A);
  MinSegmentTree s(A);
  while (Q--) {
    int L, R;
    cin >> L >> R;
    --L;
    --R;
    auto Lnode = l.query(L + 1, R - 1);
    auto Rnode = s.query(L + 1, R - 1);
    ll prod = (ll) A[L] * A[R];

    ll best = max(prod * (ll) Lnode.first * Lnode.second, prod * (ll) Rnode.first * Rnode.second);
    best = max(best, (prod * (ll) Lnode.first * Rnode.first));
    cout << best << "\n";
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}

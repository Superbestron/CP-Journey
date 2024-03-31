#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<ii> vii;

struct Node {
  bool empty;
  bool same;
  char LL;
  ll LC;
  char RL;
  ll RC;
  ll sum;
};

Node gen(int l, char c) {
  return {false, true, c, 1, c, 1, 0LL};
}

Node empty_node() {
  return {true, true, ' ', 0, ' ', 0, 0};
}

Node combine(Node left, Node right) {
  if (left.empty) return right;
  if (right.empty) return left;

  if (left.same) {
    if (right.same) {
      if (left.RL == right.LL) return {false, true, left.LL, left.LC + right.LC, left.LL, left.LC + right.LC, 0LL};
      else return {false, false, left.LL, left.LC, right.LL, right.LC, 0LL};
    } else {
      if (left.RL == right.LL) return {false, false, left.LL, left.LC + right.LC, right.RL, right.RC, right.sum};
      else return {false, false, left.LL, left.LC, right.RL, right.RC, right.sum + right.LC * right.LC};
    }
  }

  // left not same
  if (right.same) {
    if (left.RL == right.LL) return {false, false, left.LL, left.LC, right.RL, right.LC + left.RC, left.sum};
    else return {false, false, left.LL, left.LC, right.RL, right.RC, left.sum + left.RC * left.RC};
  } else {
    if (left.RL == right.LL)
      return {false, false, left.LL, left.LC, right.RL, right.RC,
              left.sum + right.sum + (left.RC + right.LC) * (left.RC + right.LC)};
    else
      return {false, false, left.LL, left.LC, right.RL, right.RC,
              left.sum + right.sum + (left.RC * left.RC) + (right.LC * right.LC)};
  }
};

class SegmentTree {
 private:
  Node build(string &s, int idx, int l, int r) {
    if (l == r) return st[idx] = gen(l, s[l]);
    int mid = (l + r) / 2;
    Node left = build(s, 2 * idx, l, mid);
    Node right = build(s, 2 * idx + 1, mid + 1, r);
    return st[idx] = combine(left, right);
  }
  Node update(int pos, char new_c, int idx, int node_l, int node_r) {
    if (node_l == node_r) {
      if (node_l == pos) st[idx] = gen(node_l, new_c);
      return st[idx];
    }
    if (pos < node_l || node_r < pos) return st[idx];
    int mid = (node_l + node_r) / 2;
    Node left = update(pos, new_c, 2 * idx, node_l, mid);
    Node right = update(pos, new_c, 2 * idx + 1, mid + 1, node_r);
    return st[idx] = combine(left, right);
  }

  Node query(int l, int r, int idx, int node_l, int node_r) {
    if (r < node_l || node_r < l) return empty_node();  // totally disjoint
    if (l <= node_l && node_r <= r) return st[idx];  // node completely in range

    // node partially in range
    int mid = (node_l + node_r) / 2;
    Node lc = query(l, r, 2 * idx, node_l, mid);
    Node rc = query(l, r, 2 * idx + 1, mid + 1, node_r);
    return combine(lc, rc);
  }

 public:
  int n;
  vector<Node> st;
  SegmentTree(string &s, int N) : n(N), st(4 * N) {
    build(s, 1, 0, n - 1);
  }
  void update(int pos, char c) {  // point update
    update(pos, c, 1, 0, n - 1);
  }
  Node query(int l, int r) {
    return query(l, r, 1, 0, n - 1);
  }
};

void solve() {
  int N, Q;
  string s;
  cin >> N >> Q >> s;

  SegmentTree st(s, N);

  int a, b;
  char c;
  while (Q--) {
    cin >> a;
    if (a == 1) {
      cin >> a >> c;
      st.update(a - 1, c);
    } else {
      cin >> a >> b;
      --a;
      --b;
      Node nd = st.query(a, b);
      if (nd.same) cout << nd.LC * nd.LC << '\n';
      else cout << nd.sum + (nd.LC * nd.LC) + (nd.RC * nd.RC) << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}

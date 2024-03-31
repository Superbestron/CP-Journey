#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef vector<ll> vll;
typedef long double ld;
typedef vector<ii> vii;
typedef pair<ll, int> lli;
typedef pair<ld, ld> ldld;
typedef vector<bool> vb;

const int INF = 1e9;
const ll LONG_INF = 1e18;

#define FOR(i, R) for (int i = 0; i < R; ++i)
#define LSOne(S) ((S) & -(S))
#define ISSET(B, i) ((B) & (1LL << (i)))
#define MSOne(x) (__lg(x))

struct Node {
  int l;
  int r;
  int size;  // r-l+1
  int num_zeroes;
  int left_zeroes;
  int right_zeroes;
};

Node gen_node_0(int l, int r) {
  int size = r - l + 1;
  return {
      l, r, size, size,
      size, size
  };
}

Node gen_node_1(int l, int r) {
  int size = r - l + 1;
  return {
      l, r, size, 0,
      0, 0
  };
}

Node combine(Node left, Node right) {
  int combined_zeroes = left.right_zeroes + right.left_zeroes;
  int ls, lsi;
  return {
      left.l, right.r,
      left.size + right.size,
      left.num_zeroes + right.num_zeroes,
      left.left_zeroes == left.size ? left.left_zeroes + right.left_zeroes : left.left_zeroes,
      right.right_zeroes == right.size ? left.right_zeroes + right.right_zeroes : right.right_zeroes,
  };
};

class SegmentTree {
 private:
  Node build(int idx, int l, int r) {
    if (l == r) return st[idx] = gen_node_0(l, l);
    int mid = (l + r) / 2;
    Node left = build(2 * idx, l, mid);
    Node right = build(2 * idx + 1, mid + 1, r);
    st[idx] = combine(left, right);
    return st[idx];
  }

  // after push_down, children have right values
  void push_down(int idx, int node_l, int node_r) {
    int lc = 2 * idx, rc = 2 * idx + 1, mid = (node_l + node_r) / 2;
    if (lazy[idx] == -1) return;
    if (lazy[idx] == 0) {
      Node lc_node = gen_node_0(node_l, mid);
      Node rc_node = gen_node_0(mid + 1, node_r);
      st[lc] = lc_node;
      st[rc] = rc_node;
      lazy[lc] = lazy[rc] = 0;
      lazy[idx] = -1;
    } else {
      Node lc_node = gen_node_1(node_l, mid);
      Node rc_node = gen_node_1(mid + 1, node_r);
      st[lc] = lc_node;
      st[rc] = rc_node;
      lazy[lc] = lazy[rc] = 1;
      lazy[idx] = -1;
    }
  }

  // update to 0 or 1
  Node update(int idx, int node_l, int node_r, int query_l, int query_r, int new_val) {
    if (query_r < node_l || node_r < query_l) return st[idx];  // totally disjoint
    if (query_l <= node_l && node_r <= query_r) {
      Node new_node = new_val == 0 ? gen_node_0(node_l, node_r) : gen_node_1(node_l, node_r);
      lazy[idx] = new_val;
      return st[idx] = new_node;  // node completely in range
    }

    // node partially in range
    push_down(idx, node_l, node_r);
    int mid = (node_l + node_r) / 2;
    Node left = update(2 * idx, node_l, mid, query_l, query_r, new_val);
    Node right = update(2 * idx + 1, mid + 1, node_r, query_l, query_r, new_val);
    return st[idx] = combine(left, right);
  }

  // query number of 0s in [query_l, query_r]
  int query(int idx, int node_l, int node_r, int query_l, int query_r) {
    if (query_r < node_l || node_r < query_l) return 0;  // totally disjoint
    if (query_l <= node_l && node_r <= query_r) return st[idx].num_zeroes;  // node completely in range

    // node partially in range
    push_down(idx, node_l, node_r);
    int mid = (node_l + node_r) / 2;
    int left = query(2 * idx, node_l, mid, query_l, query_r);
    int right = query(2 * idx + 1, mid + 1, node_r, query_l, query_r);
    return left + right;
  }

  int first_idx_gap_l(int idx, int node_l, int node_r, int l) {
    Node this_node = st[idx];
    if (node_l == node_r) return this_node.num_zeroes == l ? node_l : -1;  // leaf node: return if it has l zeroes
    if (this_node.num_zeroes < l) return -1;  // if this node doesn't even have l zeroes, it can't have l consec zeroes

    push_down(idx, node_l, node_r);  // propagate lazy update

    int mid = (node_l + node_r) / 2;
    int lc_res = first_idx_gap_l(2 * idx, node_l, mid, l);
    if (lc_res != -1) return lc_res;  // if the answer is within the left child, return first

    // if L zeroes are between left and right child
    // e.g. lc = [1111000], rc = [001111], L = 5
    // check number of "right zeroes in lc" and "left zeroes in rc"
    Node lc_node = st[2 * idx], rc_node = st[2 * idx + 1];
    if (lc_node.right_zeroes + rc_node.left_zeroes >= l) return mid - lc_node.right_zeroes + 1;

    // if the answer is within the right child, return
    int rc_res = first_idx_gap_l(2 * idx + 1, mid + 1, node_r, l);
    if (rc_res != -1) return rc_res;

    return -1;  // no answer
  }

 public:
  int n;
  vector<Node> st;
  vi lazy;
  SegmentTree(int N) : n(N), st(4 * N), lazy(4 * N, -1) {
    build(1, 0, n - 1);
  }
  void update(int l, int r, int new_val) {
    update(1, 0, n - 1, l, r, new_val);
  }
  int query(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }

  // returns leftmost index i such that [i...i+l-1] is all 0s
  // returns -1 if no such index exists
  int first_idx_gap_l(int l) {
    return first_idx_gap_l(1, 0, n - 1, l);
  }
};

void solve() {
  int n, Q;
  cin >> n >> Q;
  SegmentTree st(n);
  int q, xl, xr, l;
  int res;
  while (Q--) {
    cin >> q;
    if (q == 1) {
      cin >> l;
      res = st.first_idx_gap_l(l);
      if (res == -1) {
        cout << "-1\n";
        continue;
      }
      cout << res << '\n';
      st.update(res, res + l - 1, 1);
    } else {
      cin >> xl >> l;
      xr = xl + l - 1;
      cout << l - st.query(xl, xr) << '\n';
      st.update(xl, xr, 0);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  solve();
}

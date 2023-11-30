#include<bits/stdc++.h>
#define LSOne(S) ((S) & -(S))
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {
 private:
  vll ft;
 public:
  FenwickTree(int m) { ft.assign(m + 1, 0); }

  void build(const vll &f) {
    int m = (int) f.size() - 1;
    ft.assign(m + 1, 0);
    for (int i = 1; i <= m; ++i) {
      ft[i] += f[i];
      if (i + LSOne(i) <= m)
        ft[i + LSOne(i)] += ft[i];
    }
  }

  FenwickTree(const vll &f) { build(f); }

  FenwickTree(int m, const vi &s) {
    vll f(m + 1, 0);
    for (int i = 0; i < (int) s.size(); ++i)
      ++f[s[i]];
    build(f);
  }

  ll rsq(int j) {
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i - 1); }

  void update(int i, ll v) {
    for (; i < (int) ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {
    int p = 1;
    while (p * 2 < (int) ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i + p]) {
        k -= ft[i + p];
        i += p;
      }
      p /= 2;
    }
    return i + 1;
  }
};

class RUPQ {
 private:
  FenwickTree ft;

 public:
  RUPQ(int m) : ft(FenwickTree(m)) {}

  void range_update(int ui, int uj, ll v) {
    ft.update(ui, v);
    ft.update(uj + 1, -v);
  }

  ll point_query(int i) { return ft.rsq(i); }
};

class HLD {
 private:
  RUPQ ft;
  vi parent, depth, heavy, head, pos;
  int cur_pos;

  int dfs(int v, const vector<vector<int>> &adj) {
    int size = 1;
    int max_c_size = 0;
    for (int c : adj[v]) {
      if (c != parent[v]) {
        parent[c] = v, depth[c] = depth[v] + 1;
        int c_size = dfs(c, adj);
        size += c_size;
        if (c_size > max_c_size)
          max_c_size = c_size, heavy[v] = c;
      }
    }
    return size;
  }

  void decompose(int v, int h, const vector<vector<int>> &adj) {
    head[v] = h, pos[v] = cur_pos++;
    if (heavy[v] != -1)
      decompose(heavy[v], h, adj);
    for (int c : adj[v]) {
      if (c != parent[v] && c != heavy[v])
        decompose(c, c, adj);
    }
  }

 public:
  HLD(int sz, vector<vi> &AL) : ft(RUPQ(sz)) {
    int n = AL.size();
    parent = vector<int>(n);
    depth = vector<int>(n);
    heavy = vector<int>(n, -1);
    head = vector<int>(n);
    pos = vector<int>(n);
    cur_pos = 0;

    dfs(0, AL);
    decompose(0, 0, AL);
  }

  void update(int a, int b, ll val) {
    for (; head[a] != head[b]; b = parent[head[b]]) {
      if (depth[head[a]] > depth[head[b]])
        swap(a, b);
      ft.range_update(pos[head[b]] + 1, pos[b] + 1, val);
    }
    if (depth[a] > depth[b])
      swap(a, b);
    ft.range_update(pos[a] + 1, pos[b] + 1, val);
  }

  ll query(int i) {
    return ft.point_query(pos[i] + 1);
  }
};

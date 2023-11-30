#include <bits/stdc++.h>
using namespace std;

inline int flipOnePos(int pos, int v) {
  int num = (v >> (pos * 2)) & 3;
  num = (num + 1) % 4;
  if (num == 3) {
    v |= (1 << (pos * 2));
    v |= (1 << (pos * 2 + 1));
  } else if (num == 2) {
    v |= (1 << (pos * 2 + 1));
    v &= ~(1 << (pos * 2));
  } else if (num == 1) {
    v &= ~(1 << (pos * 2 + 1));
    v |= (1 << (pos * 2));
  } else {
    v &= ~(1 << (pos * 2 + 1));
    v &= ~(1 << (pos * 2));
  }
  return v;
}

inline int flip(int pos, int v) {
  for (int i = pos; i <= 8; i += 3) {
    v = flipOnePos(i, v);
  }
  for (int i = pos - 3; i >= 0; i -= 3) {
    v = flipOnePos(i, v);
  }
  if (pos % 3 == 0) {  // right
    v = flipOnePos(pos + 1, v);
    v = flipOnePos(pos + 2, v);
  } else if (pos % 3 == 1) {  // mid
    v = flipOnePos(pos + 1, v);
    v = flipOnePos(pos - 1, v);
  } else {  // right
    v = flipOnePos(pos - 1, v);
    v = flipOnePos(pos - 2, v);
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int val, num = 0;
  for (int i = 0; i < 9; i++) {
    cin >> val;
    if (val == 3) {
      num |= (1 << (i * 2));
      num |= (1 << (i * 2 + 1));
    } else if (val == 2) {
      num |= (1 << (i * 2 + 1));
    } else if (val == 1) {
      num |= (1 << (i * 2));
    }
  }
  queue<int> q;
  q.push(num);
  vector<int> dist(1 << 18, -1);
  dist[num] = 0;
  bool can = false;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    if (u == 0) {
      cout << dist[u];
      can = true;
      goto done;
    }
    for (int i = 0; i < 9; i++) {
      int v = flip(i, u);
      if (dist[v] != -1) continue;
      dist[v] = dist[u] + 1;
      q.push(v);
    }
  }
  done:
  if (!can) cout << -1;
}

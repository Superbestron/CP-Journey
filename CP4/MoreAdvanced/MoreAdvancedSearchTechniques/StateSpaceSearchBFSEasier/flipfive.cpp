#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int directions[2] = {3, -3};

inline int flip(int pos, int v) {
  v ^= (1 << pos);
  for (auto& dir : directions) {
    if (pos + dir >= 0 && pos + dir <= 8) {
      v ^= (1 << (pos + dir));
    }
  }
  if (pos % 3 == 0) {  // right
    v ^= (1 << (pos + 1));
  } else if (pos % 3 == 1) {  // mid
    v ^= (1 << (pos + 1));
    v ^= (1 << (pos - 1));
  } else {  // left
    v ^= (1 << (pos - 1));
  }
  return v;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int P; cin >> P;
  string str;
  while (P--) {
    int num = 0;
    for (int i = 0; i < 3; i++) {
      cin >> str;
      for (int j = 0; j < 3; j++) {
        if (str[j] == '*') num |= 1 << (i * 3 + j);
      }
    }
    queue<int> q;
    q.push(num);
    vector<int> dist(1 << 9, -1);
    dist[num] = 0;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      if (u == 0) {
        cout << dist[u] << '\n';
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
    int x;
  }
}

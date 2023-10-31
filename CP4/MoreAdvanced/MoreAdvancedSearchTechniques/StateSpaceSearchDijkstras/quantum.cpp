#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int> ii;
const int INF = 1e9;

int N, L, nop, nw, c;

int convert_dec(string &n) {
  int dec_value = 0, base = 1, len = n.length();
  for (int i = len - 1; i >= 0; i--) {
    if (n[i] == '1')
      dec_value += base;
    base <<= 1;
  }
  return dec_value;
}

string convert_int(int n) {
  string ans;
  for (int i = L - 1; i >= 0; i--) {
    int k = n >> i;
    if (k & 1) ans += "1";
    else ans += "0";
  }
  return ans;
}

int perform_op(string s, string &op) {
  for (int i = 0; i < s.size(); i++) {
    if (op[i] == 'F') {
      s[i] = s[i] == '0' ? '1' : '0';
    } else if (op[i] == 'S') {
      s[i] = '1';
    } else if (op[i] == 'C') {
      s[i] = '0';
    }
  }
  return convert_dec(s);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string word, src, dest;
  cin >> N;
  while (N--) {
    cin >> L >> nop >> nw;
    vector<tuple<string, int>> v;
    for (int i = 0; i < nop; i++) {
      cin >> word >> c;
      v.emplace_back(word, c);
    }
    for (int i = 0; i < nw; i++) {
      cin >> src >> dest;
      int src_num = convert_dec(src);
      int dest_num = convert_dec(dest);
      vector<int> dist(1 << L, INF);
      dist[src_num] = 0;
      priority_queue<ii, vector<ii>, greater<>> pq;
      pq.emplace(0, src_num);
      while (!pq.empty()) { // main loop
        auto [d, u] = pq.top();
        pq.pop(); // shortest unvisited u
        if (d > dist[u]) continue; // a very important check
        string u_str = convert_int(u);
        for (int j = 0; j < nop; j++) {
          string &op = get<0>(v[j]);
          int cost = get<1>(v[j]);
          int res = perform_op(u_str, op);
          if (dist[res] <= d + cost) continue;
          dist[res] = d + cost;
          pq.emplace(dist[res], res);
        }
      }
      cout << (dist[dest_num] == INF ? "NP" : to_string(dist[dest_num])) << ' ';
    }
    cout << '\n';
  }
}
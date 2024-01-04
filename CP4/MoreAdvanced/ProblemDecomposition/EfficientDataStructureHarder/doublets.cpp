#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// Spent 5 hours optimising this shit hole of a question
// As per the section in the question, you REALLY need to use an efficient data structure
// Finally got 0.95s AC
// I only compared strings which are worth comparing (i.e. compare only size n strings if there is
// a size n string in the query)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  string s, s1, s2;
  int MAX_N = 25143;
  string v[MAX_N], v2[MAX_N];
  unordered_map<string, int> m;
  vector<unordered_set<char>> char_pos(17);
  unordered_map<int, vector<int>> AL[17];


  int ctr = 0;
  while (getline(cin, s)) {
    if (s.empty()) break;
    v2[ctr++] = std::move(s);
  }

  int dist[ctr], p[ctr];
  vector<pair<string, string>> strings;
  unordered_set<int> sizes;
  while (cin >> s1 >> s2) {
    strings.emplace_back(s1, s2);
    if (s1.size() == s2.size() && s1 != s2) sizes.insert(s1.size());
  }

  ctr = 0;
  for (auto &i : v2) {
    if (!sizes.count(i.size())) continue;
    v[ctr++] = std::move(i);
  }

  for (int j = 0; j < ctr; j++) {
    string &str = v[j];
    m[str] = j;
    for (int i = 0; i < str.size(); ++i) {
      for (char new_ch : char_pos[i]) {
        if (new_ch != str[i]) {
          string neighbor = str;
          neighbor[i] = new_ch;

          // Check if possible neighbor is an actual neighbor
          if (m.count(neighbor)) {
            int sz = str.size();
            int idx1 = m[neighbor];
            AL[sz][idx1].push_back(j);
            AL[sz][j].push_back(idx1);
          }
        }
      }
    }
    int pos = 0;
    for (char ch : str) {
      char_pos[pos].insert(ch);
      pos++;
    }
  }

  for (auto &[s3, s4] : strings) {
    if (s3.size() != s4.size()) cout << "No solution.\n\n";
    else {
      if (s3 == s4) cout << s3 << "\n\n";
      else {
        int sz = s3.size(), source = m[s3], sink = m[s4];
        memset(dist, -1, sizeof dist);
        memset(p, -1, sizeof p);
        queue<int> q;
        dist[source] = 0;
        q.push(source);

        while (!q.empty()) {
          int u = q.front(); q.pop();
          for (int v : AL[sz][u]) {
            if (dist[v] != -1) continue;
            dist[v] = dist[u] + 1;
            p[v] = u;
            if (v == sink) goto done;
            q.push(v);
          }
        }
        done:
        if (dist[sink] == -1) cout << "No solution.\n\n";
        else {
          vector<int> ans({sink});
          int curr = sink;
          while (p[curr] != -1) {
            ans.push_back(p[curr]);
            curr = p[curr];
          }
          for (auto it = ans.rbegin(); it != ans.rend(); it++) {
            cout << v[*it] << '\n';
          }
          cout << '\n';
        }
      }
    }
  }
}

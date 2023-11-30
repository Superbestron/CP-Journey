#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi match, vis;
vector<vi> AL;

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, V = 1000;
  cin >> N;
  unordered_set<int> s;
  match.assign(V, -1);
  AL.assign(V, {});
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    x--; y--;
    AL[x].push_back(y + 500);
    AL[y + 500].push_back(x);
    s.insert(x);
    s.insert(y + 500);
  }
  int MCBM = 0;
  unordered_set<int> freeV;
  for (int L = 0; L < 500; ++L)
    freeV.insert(L);
  // Greedy pre-processing for trivial Augmenting Paths
  // try commenting versus un-commenting this for-loop
  for (int L = 0; L < 500; ++L) {              // O(V+E)
    vi candidates;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int)candidates.size() > 0) {
      ++MCBM;
      freeV.erase(L);                            // L is matched
      int a = rand()%(int)candidates.size();     // randomize this
      match[candidates[a]] = L;
    }
  }                                          // for each free vertex
  for (auto &f : freeV) {                        // (in random order)
    vis.assign(V, 0);                        // reset first
    MCBM += Aug(f);                              // try to match f
  }
  if (MCBM * 2 == s.size()) cout << "Slavko\n";
  else cout << "Mirko\n";
}

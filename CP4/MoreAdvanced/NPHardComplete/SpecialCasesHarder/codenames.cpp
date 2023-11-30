#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int> iii;

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

bool is_swap_free(string &s1, string &s2) {
  int diff_count = 0;
  for (int i = 0; i < s1.size(); i++) {
    if (s1[i] != s2[i]) diff_count++;
    if (diff_count > 2) return true;
  }
  return diff_count != 2;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N;
  string s;
  vector<string> v;
  cin >> N;
  int V = N;
  unordered_set<int> freeV;
  for (int L = 0; L < V; ++L)
    freeV.insert(L);                             // initial assumption
  AL.assign(V, {});
  for (int i = 0; i < N; i++) {
    cin >> s;
    freeV.insert(i);
    for (int j = 0; j < v.size(); j++) {
      if (!is_swap_free(s, v[j])) {
        if (freeV.count(j)) freeV.erase(i);
        AL[i].push_back(j);
        AL[j].push_back(i);
      }
    }
    v.push_back(std::move(s));
  }

  match.assign(V, -1);

  int MCBM = 0;
  // Greedy pre-processing for trivial Augmenting Paths
  // try commenting versus un-commenting this for-loop
  for (auto it = freeV.begin(); it != freeV.end();) {  // O(V+E)
    vi candidates;
    int L = *it;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int)candidates.size() > 0) {
      ++MCBM;
      it = freeV.erase(it);                            // L is matched
      int a = rand()%(int)candidates.size();     // randomize this
      match[candidates[a]] = L;
    } else it++;
  }                                                  // for each free vertex
  for (int L : freeV) {                        // (in random order)
    vis.assign(V, 0);                        // reset first
    MCBM += Aug(L);                              // try to match f
  }
  cout << N - MCBM << '\n';
}

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;

class MCBM {
 private:
  vi match, vis;                                   // global variables
  vector<vi> AL;
  unordered_set<int> freeV;
  int V, matchings;

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
 public:
  MCBM(vector<vi> &AL, unordered_set<int> &freeV) : V(AL.size()), AL(AL), freeV(freeV) {
    match.assign(V, -1);
  }
  int get_matchings() {
    matchings = 0;
    for (auto it = freeV.begin(); it != freeV.end();) {              // O(V+E)
      vi candidates;
      int L = *it;
      for (auto &R : AL[L])
        if (match[R] == -1)
          candidates.push_back(R);
      if ((int) candidates.size() > 0) {
        ++matchings;
        it = freeV.erase(it);                            // L is matched
        int a = rand() % (int) candidates.size();     // randomize this
        match[candidates[a]] = L;
      } else it++;
    }
    for (auto &f : freeV) {                        // (in random order)
      vis.assign(V, 0);                        // reset first
      matchings += Aug(f);                              // try to match f
    }
    return matchings;
  }
};

int main() {
  unordered_set<int> freeV;
  vector<vi> AL;
  int V = 20, Vleft = 10;
  for (int L = 0; L < Vleft; ++L)
    freeV.insert(L);                             // initial assumption
  MCBM mcbm(AL, freeV);
  cout << "Found " << mcbm.get_matchings() << " matchings\n";    // the answer is 2 for Figure 4.38
}

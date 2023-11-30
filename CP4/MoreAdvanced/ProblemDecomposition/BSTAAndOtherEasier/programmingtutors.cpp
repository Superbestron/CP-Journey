#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vector<vi> AL;
vector<pair<int, int>> students, tutors;
unordered_set<int> freeV;
int N, x, y;

class MCBM {
 private:
  vi match, vis;                                   // global variables
  vector<vi> AL;
  unordered_set<int> freeV;
  int V, matchings;
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
};

bool can(int cap) {
  AL.assign(2 * N, {});
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      int dist = abs(students[i].first - tutors[j].first) + abs(students[i].second - tutors[j].second);
      if (dist <= cap) {
        AL[i].push_back(N + j);
        AL[N + j].push_back(i);
      }
    }
  }
  MCBM mcbm(AL, freeV);
  int ans = mcbm.get_matchings();
  return ans == N;
}

int main() {
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    students.emplace_back(x, y);
  }
  for (int i = 0; i < N; i++) {
    cin >> x >> y;
    tutors.emplace_back(x, y);
  }
  int lo = 0, hi = 1e9;
  for (int i = 0; i < N; i++) freeV.insert(i);
  while (hi > lo) {
    int mid = lo + (hi - lo) / 2;
    can(mid) ? hi = mid : lo = mid + 1;
  }
  cout << lo << '\n';
}

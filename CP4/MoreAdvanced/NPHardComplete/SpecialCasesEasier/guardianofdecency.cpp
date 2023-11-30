#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, char, string, string> iiii;
typedef vector<int> vi;

vi match, vis;                                   // global variables
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
  int N, h;
  char gender;
  string music, sport;
  cin >> N;
  vector<iiii> v;
  AL.assign(N, {});
  unordered_set<int> freeV;
  for (int i = 0; i < N; i++) {
    cin >> h >> gender >> music >> sport;
    if (gender == 'M') freeV.insert(i);
    for (int j = 0; j < v.size(); j++) {
      int h_diff = abs(get<0>(v[j]) - h);
      if (h_diff <= 40 && gender != get<1>(v[j]) && music == get<2>(v[j]) && sport != get<3>(v[j])) {
        AL[i].push_back(j);
        AL[j].push_back(i);
      }
    }
    v.emplace_back(h, gender, std::move(music), std::move(sport));
  }

  match.assign(N, -1);
  int MCBM = 0;
  for (auto it = freeV.begin(); it != freeV.end();) {              // O(V+E)
    int L = *it;
    vi candidates;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int) candidates.size() > 0) {
      ++MCBM;
      it = freeV.erase(it);                            // L is matched
      int a = rand() % (int) candidates.size();     // randomize this
      match[candidates[a]] = L;
    } else it++;
  }                                              // for each free vertex
  for (auto &f : freeV) {                        // (in random order)
    vis.assign(N, 0);                        // reset first
    MCBM += Aug(f);                              // try to match f
  }
  cout << N - MCBM << '\n';
}

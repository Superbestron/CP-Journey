#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

vi match, vis;
vector<vi> dist;

inline int convertToIdx(int i, int j, int w) {
  return i * w + j;
}

int Aug(int L) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : dist[L])
    if ((match[R] == -1) || Aug(match[R])) {
      match[L] = R;
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, h, w;
  int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
  cin >> n;
  while (n--) {
    cin >> h >> w;
    vector<string> v(h);
    dist.assign(h * w, {});
    for (auto& str : v) cin >> str;
    int V = h * w;
    unordered_set<int> freeV;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (v[i][j] == 'o') continue;
        if (i & 1) {
          if (j & 1) {
            freeV.insert(convertToIdx(i, j, w));
            for (auto& direction : directions) {
              int new_x = i + direction[0];
              int new_y = j + direction[1];
              if (new_x < 0 || new_x == h || new_y < 0 || new_y == w || v[new_x][new_y] == 'o') continue;
              dist[convertToIdx(i, j, w)].push_back(convertToIdx(new_x, new_y, w));
            }
          }
        } else {
          if ((j & 1) == 0) {
            freeV.insert(convertToIdx(i, j, w));
            for (auto& direction : directions) {
              int new_x = i + direction[0];
              int new_y = j + direction[1];
              if (new_x < 0 || new_x == h || new_y < 0 || new_y == w || v[new_x][new_y] == 'o') continue;
              dist[convertToIdx(i, j, w)].push_back(convertToIdx(new_x, new_y, w));
            }
          }
        }
      }
    }
    match.assign(V, -1);
    int MCBM = 0;
    // Greedy pre-processing for trivial Augmenting Paths
    // try commenting versus un-commenting this for-loop
    for (auto it = freeV.begin(); it != freeV.end();) {              // O(V+E)
      vi candidates;
      for (auto &R : dist[*it])
        if (match[R] == -1)
          candidates.push_back(R);
      if ((int)candidates.size() > 0) {
        ++MCBM;
        int a = rand()%(int)candidates.size();     // randomize this
        match[candidates[a]] = *it;
        match[*it] = candidates[a];
        it = freeV.erase(it);
      } else {
        it++;
      }
    }                                              // for each free vertex
    for (auto &f : freeV) {                        // (in random order)
      vis.assign(V, 0);                        // reset first
      MCBM += Aug(f);                              // try to match f
    }
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (v[i][j] == 'o') continue;
        if (match[convertToIdx(i, j, w)] == -1) MCBM++;
      }
    }
    cout << MCBM << '\n';
  }
}
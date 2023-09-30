#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef tuple<int, int, int, int, int> iiiii;

vi match, vis;
vector<vi> AL;

vector<string> split(string& s, char delimiter) {
  size_t pos;
  string token;
  vector<string> arr;
  if (s.empty()) return arr;
  while ((pos = s.find(delimiter)) != string::npos) {
    token = s.substr(0, pos);
    arr.emplace_back(token);
    s.erase(0, pos + 1);
  }
  arr.emplace_back(s);
  return arr;
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

inline int dist(int a, int b, int c, int d) {
  return abs(a - c) + abs(b - d);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, M, a, b, c, d;
  string s;
  cin >> N;
  while (N--) {
    cin >> M;
    vector<iiiii> trips;
    for (int i = 0; i < M; i++) {
      cin >> s >> a >> b >> c >> d;
      vector<string> v(split(s, ':'));
      int hour = stoi(v[0]), min = stoi(v[1]);
      trips.emplace_back(hour * 60 + min, a, b, c, d);
    }

    int V = 2 * M, Vleft = M;
    AL.assign(V, {});

    // construct graph
    // only have an edge if a plane is able to finish its flight and also start another flight
    for (int i = 0; i < M; i++) {
      auto& t1 = trips[i];
      for (int j = 0; j < M; j++) {
        if (i != j) {
          auto& t2 = trips[j];
          int finish_t1_time = get<0>(t1) + dist(get<1>(t1), get<2>(t1), get<3>(t1), get<4>(t1));
          int shortest_time_to_t2_src = dist(get<3>(t1), get<4>(t1), get<1>(t2), get<2>(t2));
          if (finish_t1_time + shortest_time_to_t2_src < get<0>(t2)) {
            AL[i].push_back(j + M);
          }
        }
      }
    }

    unordered_set<int> freeV;
    for (int L = 0; L < Vleft; ++L)
      freeV.insert(L);                             // initial assumption
    match.assign(V, -1);

    int MCBM = 0;
    // Greedy pre-processing for trivial Augmenting Paths
    // try commenting versus un-commenting this for-loop
    for (int L = 0; L < Vleft; ++L) {              // O(V+E)
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
    }                                                  // for each free vertex
    for (int L : freeV) {                        // (in random order)
      vis.assign(Vleft, 0);                        // reset first
      MCBM += Aug(L);                              // try to match f
    }
    cout << M - MCBM << '\n';
  }
}
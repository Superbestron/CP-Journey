#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef int16_t int16;
typedef vector<int16> vi;
typedef set<pair<int, int16>, greater<>> maxheap;
#define TIME_MS 1975
#define LSOne(S) S & (-S)

int16 nodes, k;
int min_link, max_link;
ll length, best_length;
vi tour, best_tour, position;
vector<deque<int16>> knn;
vector<vector<int>> dist;
vector<pair<double,double>> coord;
chrono::time_point<chrono::steady_clock> start_time = chrono::steady_clock::now();

class UnionFind {
 private:
  vi p, rank, setSize;
  int16 numSets;

 public:
  UnionFind(int N) {
    p.assign(N, 0);
    for (int i = 0; i < N; i++) p[i] = i;
    rank.assign(N, 0);
    setSize.assign(N, 1);
    numSets = N;
  }

  int16 findSet(int16 i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int16 i, int16 j) { return findSet(i) == findSet(j); }
  int16 numDisjointSets() { return numSets; }
  int16 sizeOfSet(int16 i) { return setSize[findSet(i)]; }

  void unionSet(int16 i, int16 j) {
    if (isSameSet(i, j)) return;
    int16 x = findSet(i), y = findSet(j);
    if (rank[x] > rank[y]) swap(x, y);
    p[x] = y;
    if (rank[x] == rank[y]) rank[y]++;
    setSize[y] += setSize[x];
    numSets--;
  }
};


inline void update(int16 i, int16 j) {
  //assert(i != j);
  if (j < i) swap(i, j);
  reverse(tour.begin() + i, tour.begin() + j);
  for (; i < j; i++) position[tour[i]] = i;
}

void ls2opt() {
  bool imp = true;
  int twoOps = 0;
  while (imp) {
    imp = false;
    if (chrono::steady_clock::now() - start_time > chrono::milliseconds(TIME_MS)) return;
    for (int16 i = 0; i < nodes; i++) {
      for (auto &j : knn[tour[i]]) {
        int16 i1 = i;
        int16 j1 = (i1 + 1) % nodes; // curr i1-j1
        int16 i2 = position[j];
        int16 j2 = (i2 + 1) % nodes; // curr i2-j2

        if (j1 == i2 || j2 == i1)
          continue;

        if (dist[tour[i1]][tour[i2]] + min_link > dist[tour[j1]][tour[i1]] + max_link)
          break;

        if (i1 > i2)
          swap(i1,i2), swap(j1,j2);
        //assert(i2-i1>1);
        int diff = dist[tour[i1]][tour[j1]] + dist[tour[i2]][tour[j2]] - dist[tour[i1]][tour[i2]] - dist[tour[j1]][tour[j2]];

        if (diff > 0) {
          max_link = max(max_link, max(dist[tour[i1]][tour[i2]], dist[tour[j1]][tour[j2]]));
          update(i1+1, i2+1); // to be optimized?
          length -= diff;
          imp = true;
          twoOps++;
          //int checkDist = 0;
          //for (int i=0;i<nodes;i++) checkDist += dist[tour[i]][tour[(i+1)%nodes]];
          //assert(checkDist == dist);
          break;
        }
      }
    }
  }
  //cout << "twoOps:" << twoOps <<'\n';
}

bool ls3opt() {
  bool worked = false;
  bool improvement = true;
  //int threeOps = 0;
  while (improvement) {
    if (chrono::steady_clock::now() - start_time > chrono::milliseconds(TIME_MS)) return false;
    improvement = false;
    for (int16 i1 = 0; i1 < nodes; i1++) {
      int16 j1 = (i1 + 1) % nodes; // curr i1-j1
      for (auto &j : knn[tour[j1]]) {
        int16 i2 = position[j];
        int16 j2 = (i2 + 1) % nodes; // curr i2-j2

        if (i1 == i2 || j2 == i1 || i2 == j1) continue;
        //assert(j2 != i1 && i2 != j1);
        if (dist[tour[j1]][tour[i2]] + min_link * 2 > dist[tour[j1]][tour[i1]] + max_link * 2)
          break;

        if (dist[tour[j1]][tour[i2]] + min_link * 2 > dist[tour[j1]][tour[i1]] + dist[tour[j2]][tour[i2]] + max_link)
          continue;

        for (auto &k : knn[tour[i1]]) {
          int16 i3 = position[k];
          int16 j3 = (i3 + 1) % nodes;

          if (i1 == i3 || i1 == j3 || j1 == i3 || i2 == i3 || i2 == j3 || i3 == j2 )
            continue;

          if (dist[tour[j1]][tour[i2]] + dist[tour[i1]][tour[i3]] + min_link >
              dist[tour[j1]][tour[i1]] + dist[tour[j2]][tour[i2]] + max_link)
            break;

          int16 x1 = i1, y1 = j1, x2 = i2, y2 = j2, x3 = i3, y3 = j3;
          if (x1 > x2) swap(x1, x2), swap(y1, y2);
          if (x2 > x3) swap(x2, x3), swap(y2, y3);
          if (x1 > x2) swap(x1, x2), swap(y1, y2);
          //assert(x2-x1>1);
          //assert(x3-x2>1);
          int original = dist[tour[x1]][tour[y1]] + dist[tour[x2]][tour[y2]] + dist[tour[x3]][tour[y3]];

          int alt = dist[tour[x1]][tour[y2]] + dist[tour[x3]][tour[x2]] + dist[tour[y1]][tour[y3]];
          if (original - alt > 0) {
            max_link = max({max_link, dist[tour[x1]][tour[y2]], dist[tour[x3]][tour[x2]], dist[tour[y1]][tour[y3]]});
            length -= original - alt;
            update(x1 + 1, x3 + 1);
            update(x1 + 1, x1 + x3 - x2 + 1);
            goto updated;
          }
          alt = dist[tour[x1]][tour[x2]] + dist[tour[y1]][tour[x3]] + dist[tour[y2]][tour[y3]];
          if (original - alt > 0) {
            max_link = max({max_link, dist[tour[x1]][tour[x2]], dist[tour[y1]][tour[x3]], dist[tour[y2]][tour[y3]]});
            length -= original - alt;
            update(x1 + 1, x2 + 1);
            update(x2 + 1, x3 + 1);
            goto updated;
          }
          alt = dist[tour[x1]][tour[x3]] + dist[tour[y2]][tour[y1]] + dist[tour[x2]][tour[y3]];
          if (original - alt > 0) { // i1 i3-j2 j1-i2 j3s
            max_link = max({max_link, dist[tour[x1]][tour[x3]], dist[tour[y2]][tour[y1]], dist[tour[x2]][tour[y3]]});
            length -= original - alt;
            update(x1 + 1, x3 + 1);
            update(x1 + x3 - x2 + 1, x3 + 1);
            goto updated;
          }
          alt = dist[tour[x1]][tour[y2]] + dist[tour[x3]][tour[y1]] + dist[tour[x2]][tour[y3]];
          if (original - alt > 0) { // i1 i2-i3 j1-i2 j3
            max_link = max({max_link, dist[tour[x1]][tour[y2]], dist[tour[x3]][tour[y1]], dist[tour[x2]][tour[y3]]});
            length -= original - alt;
            update(x1 + 1, x3 + 1);
            update(x1 + 1, x1 + x3 - x2 + 1);
            update(x1 + x3 - x2 + 1, x3 + 1);
            goto updated;
          }
          continue;
          //for (int b=0;b<nodes;b++) assert(tour[position[b]] == b);
          updated:
          //assert(dist>=0);
          //threeOps++;
          improvement = true;
          worked = true;
          //ll checkDist = 0;
          //for (int i=0;i<nodes;i++) checkDist += dist[tour[i]][tour[(i+1)%nodes]];
          //assert(checkDist == length);
          goto outer;
        }
      }
      outer:
      continue;
    }
  }
  return worked;
  //cout << "threeOps:" << threeOps << '\n';
}

void rand4opt(){ // only works if nodes > 12,
  int16 i1,j1,i2=-1,j2,i3,j3,i4=-1,j4;
  unordered_set<int16> disallowed_positions;
  i1 = rand() % nodes;
  j1 = (i1+1) % nodes;
  for (int i=(i1-1+nodes)%nodes,j=0;j<4;i=(i+1)%nodes,j++) disallowed_positions.emplace(i);
  deque<int16> r_knn1 = knn[tour[i1]], r_knn2 = knn[tour[j1]];
  random_shuffle(r_knn1.begin(), r_knn1.end());
  random_shuffle(r_knn2.begin(), r_knn2.end());
  for (auto& cand1:r_knn1) for (auto& cand2:r_knn2) {
      int16 td = abs(position[cand1]-position[cand2]);
      if ((td == 1 || td == nodes-1)) {
        i2 = position[cand1];
        j2 = position[cand2];
        if (!disallowed_positions.count(i2) && !disallowed_positions.count(j2)) break;
        i2 = -1;
      }
    }
  if (i2 == -1) {
    while(true) {
      i2 = rand() % nodes;
      j2 = (i2+1) % nodes;
      if (!disallowed_positions.count(i2) && !disallowed_positions.count(j2)) break;
    }
  }
  disallowed_positions.erase((i1-1+nodes)%nodes);
  disallowed_positions.erase((j1+1)%nodes);
  disallowed_positions.emplace(i2), disallowed_positions.emplace(j2);
  while(true){
    i3 = rand() % nodes;
    j3 = (i3+1) % nodes;
    if (!disallowed_positions.count(i3) && !disallowed_positions.count(j3)) break;
  }
  for (int i=(i3-1+nodes)%nodes,j=0;j<4;i=(i+1)%nodes,j++) disallowed_positions.emplace(i);
  r_knn1 = knn[tour[i3]], r_knn2 = knn[tour[j3]];
  random_shuffle(r_knn1.begin(), r_knn1.end());
  random_shuffle(r_knn2.begin(), r_knn2.end());
  for (auto& cand1:r_knn1) for (auto& cand2:r_knn2) {
      int16 td = abs(position[cand1]-position[cand2]);
      if ((td == 1 || td == nodes-1)) {
        i4 = position[cand1];
        j4 = position[cand2];
        if (!disallowed_positions.count(i4) && !disallowed_positions.count(j4)) break;
        i4 = -1;
      }
    }
  if (i4 == -1) {
    while(true) {
      i4 = rand() % nodes;
      j4 = (i4+1) % nodes;
      if (!disallowed_positions.count(i4) && !disallowed_positions.count(j4)) break;
    }
  }
  if ((i1 == 0 && j1 == nodes-1) || (i1>j1 && i1 != nodes-1)) swap(i1,j1);
  if ((i2 == 0 && j2 == nodes-1) || (i2>j2 && i2 != nodes-1)) swap(i2,j2);
  if ((i3 == 0 && j3 == nodes-1) || (i3>j3 && i3 != nodes-1)) swap(i3,j3);
  if ((i4 == 0 && j4 == nodes-1) || (i4>j4 && i4 != nodes-1)) swap(i4,j4);

  vector<pair<int16,int16>> ordered_positions({{i1,j1},{i2,j2},{i3,j3},{i4,j4}});
  sort(ordered_positions.begin(), ordered_positions.end());
  tie(i1,j1) = ordered_positions[0];
  tie(i2,j2) = ordered_positions[1];
  tie(i3,j3) = ordered_positions[2];
  tie(i4,j4) = ordered_positions[3];
  length -= dist[tour[i1]][tour[j1]] + dist[tour[i2]][tour[j2]] + dist[tour[i3]][tour[j3]] + dist[tour[i4]][tour[j4]];
  length += dist[tour[i1]][tour[j3]] + dist[tour[i3]][tour[j1]] + dist[tour[i4]][tour[j2]] + dist[tour[i2]][tour[j4]];
  max_link = max({max_link, dist[tour[i1]][tour[j3]], dist[tour[i3]][tour[j1]], dist[tour[i4]][tour[j2]], dist[tour[i2]][tour[j4]]});
  update(i1+1, i4+1);
  update(i1+1, i1+i4-i3+1);
  update(i1+i4-i3+1, i1+i4-i2+1);
  update(i1+i4-i2+1, i4+1);
  /* assert(i1+1<i2 && i2+1<i3 && i3+1<i4 && i4<nodes);
  ll checkDist = 0;
  for (int i=0;i<nodes;i++) checkDist += dist[tour[i]][tour[(i+1)%nodes]];
  assert(checkDist == length); */
}

void init_large(){
  tour.assign(nodes, 0);
  dist.assign(nodes, vector<int>(nodes));
  coord.assign(nodes, {0,0});
  position.assign(nodes, 0);
  min_link = INT_MAX;
  max_link = 0;
  length = 0;
  best_length = INT_MAX;
  k = 20;
  knn.assign(nodes, deque<int16>());
  for (auto&[x,y]:coord) {
    //x = rand() % 1000000;
    //y = rand() % 1000000;
//    int dummy;
//    cin >> dummy >> x >> y;
    cin >> x >> y;
  }
  for (int i=0;i<nodes;i++) {
    auto&[ix,iy] = coord[i];
    for (int j=i;j<nodes;j++) {
      auto&[jx,jy] = coord[j];
      dist[i][j] = round(hypot(ix-jx,iy-jy));
      dist[j][i] = dist[i][j];
      if (i != j) min_link = min(min_link, dist[i][j]);
    }
  }
}

void generate_knn() { // O(Nlog(k))
  for (int16 i=0;i<nodes;i++) {
    maxheap pq;
    for (int16 j=0;j<nodes;j++) {
      if (i != j && (pq.size()<k || dist[i][j] < pq.begin()->first)) pq.insert({dist[i][j],j});
      if (pq.size()>k) pq.erase(pq.begin());
    }
    for (auto[d,idx]:pq) knn[i].emplace_front(idx);
  }
}

void generate_start_tour() { // O(N^2);
  vector<bool> used(nodes);
  vector<pair<int16,int16>> link(nodes,{-1,-1});
  UnionFind uf(nodes);
  for (int16 loop=0;loop<2;loop++){
    for (int16 i=0;i<nodes;i++) {
      if (used[i]) continue;
      int16 best_idx = -1;
      int bd = 1e9;
      for (int16 j=0;j<nodes;j++) {
        if (i != j
            && dist[i][j] < bd
            && !used[j]
            && (!uf.isSameSet(i,j)
                || uf.sizeOfSet(i) == nodes)) {
          best_idx = j;
          bd = dist[i][j];
        }
      }
      uf.unionSet(i,best_idx);
      auto&[i1,i2] = link[i];
      auto&[j1,j2] = link[best_idx];
      if (i1 == -1) i1 = best_idx; else i2 = best_idx, used[i] = true;
      if (j1 == -1) j1 = i; else j2 = i, used[best_idx] = true;
    }
  }
  used.assign(nodes,false);
  used[0] = true;
  tour[0] = 0;
  for (int16 i = 1; i < nodes; i++) {
    auto&[j,k] = link[tour[i - 1]];
    if (!used[j]) {
      tour[i] = j;
      used[j] = true;
    } else if (!used[k]){
      tour[i] = k;
      used[k] = true;
    }
  }
  for (int16 i = 0; i < nodes; i++) {
    position[tour[i]] = i;
    int path_length = dist[tour[i]][tour[(i + 1) % nodes]];
    max_link = max(max_link, path_length);
    length += path_length;
  }
}

ll dp(int u, int mask, int d, vector<vector<ll>> &memo) { // mask = free coordinates
  if (mask == 0) {
    if (d + dist[u][0] < best_length) {
      best_tour = tour;
      best_length = d + dist[u][0];
    }
    return dist[u][0]; // close the tour
  }
  ll &ans = memo[u][mask];
  if (ans != -1) return ans; // computed before
  ans = 1e18;
  int m = mask;
  while (m) { // up to O(n)
    int two_pow_v = LSOne(m); // but this is fast
    int v = __builtin_ctz(two_pow_v) + 1; // offset v by +1
    tour.push_back(v);
    //ans = min(ans, dp(v, mask ^ two_pow_v, d + dist[u][v])); // keep the min
    ans = min(ans,  dp(v, mask ^ two_pow_v, d + dist[u][v], memo) + dist[u][v]); // keep the min
    tour.pop_back();
    m -= two_pow_v;
  }
  return ans;
}

void help_karp() {
  vector<vector<ll>> memo(nodes, vector<ll>(1 << (nodes-1), -1));
  dist.assign(nodes, vector<int>(nodes, 1e9));
  coord.assign(nodes,{0,0});

  best_length = 1e18;
  for (auto &[a,b]:coord) cin >> a >> b;
  for (int i = 0; i < nodes; i++) {
    for (int j = i + 1; j < nodes; j++) {
      dist[i][j] = dist[j][i] = round(hypot(coord[i].first - coord[j].first, coord[i].second - coord[j].second));
    }
  }
  ll ans = dp(0, (1 << (nodes - 1)) - 1, 0, memo);
  //cout << ans << '\n';
  cout << 0 << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> nodes;
  srand(7);
  if (nodes > 19) {
    init_large();
    generate_start_tour();
    generate_knn();
    while (true){
      ls2opt();
      while(ls3opt()) ls2opt();
      if (length < best_length) best_tour = tour, best_length = length;
      if (chrono::steady_clock::now() - start_time > chrono::milliseconds(TIME_MS)) break;
      rand4opt();
    }
  } else {
    help_karp();
  }
  //chrono::steady_clock::time_point end_time = chrono::steady_clock::now();
  //cout << chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() << '\n';
//  cout << best_length << '\n';
  for (int i : best_tour) cout << i << '\n';
}

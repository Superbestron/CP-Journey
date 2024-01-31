#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vi> vvi;
const double EPS = 1e-9;
const ll INF = 1e12;

// Use a convex hull DP optimisation technique, with parabolas instead of lines
// With reference from Brandon Tang

// m here is not the gradient but rather the y
struct tline { ll m, c; double p; };
vector<tline> lines;

int n, c;

// Solving for x as (y1 - x)^2 + c = (y2 - x)^2 + c
double getX(ll m1, ll c1, ll m2, ll c2) {
  return ((double) (m1 * m1 - m2 * m2 + c1 - c2)) / (2 * (m1 - m2));
}

void addLine(ll m, ll c) {
  double p = -INF;
  while (!lines.empty()) {
    p = getX(m, c, lines.back().m, lines.back().c);
    if (p < lines.back().p - EPS) lines.pop_back();
    else break;
  }
  lines.push_back((tline) {m, c, p});
}

ll getBestY(ll x) {
  static int k = 0;
  k = min(k, (int) lines.size() - 1);
  while (k + 1 < lines.size() && lines[k + 1].p <= x + EPS) ++k;
  return (x - lines[k].m) * (x - lines[k].m) + lines[k].c + c;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> c;
  vll A(n);
  for (ll &i : A) cin >> i;
  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    addLine(A[i], ans);
    ans = getBestY(A[i]);
  }
  cout << ans << '\n';
}

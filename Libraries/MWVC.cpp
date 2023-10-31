#include<bits/stdc++.h>

using namespace std;
#define LSOne(S) ((S) & -(S))
#define randP(l,r) l + rand()%(r-l+1);

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<int> v(8), m(8);
    for (int i=0;i<8;i++) cin >> v[i];
    int e; cin >> e;
    const int f = (1<<e) - 1;
    for (int i=0;i<e;i++) {
        int x,y; cin >> x >> y;
        m[x] |= (1<<i);
        m[y] |= (1<<i);
    }
    int mn = 1e9;
    for (int i=0;i<(1<<8);i++) {
        int j = 0, t = 0;
        for (int x=0;x<8;x++) {
            if (i&(1<<x)) j |= m[x], t += v[x];
        }
        if (j == f) mn = min(mn,t);
    }
    cout << mn;
}
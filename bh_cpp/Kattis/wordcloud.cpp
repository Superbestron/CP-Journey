#include<bits/stdc++.h>
#include<cmath>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    int W,N,count;
    int cmax,ans,cwidth,width,pt,o,hmax;
    string s;
    while (++count){
        cin >> W >> N;
        if (W == 0 && N == 0) break;
        cmax = 0, ans = 0, cwidth = 0; hmax = 0;
        vector<pair<int,int>> v;
        while (N--){
            cin >> s >> o;
            v.push_back(pair<int,int>{s.length(),o});
            cmax = max(cmax,o);
        }
        for (int i=0;i<v.size();i++){
            pt = ceil((double)8 + ((double)40 * (v[i].second - 4) / (cmax - 4)));
            width = ceil((double)9 / 16 * v[i].first * pt);
            if (cwidth + width <= W){
                hmax = max(hmax,pt);
                cwidth += width + 10;
            } else {
                ans += hmax;
                cwidth = width + 10;
                hmax = pt;
            }
        }
        ans += hmax;
        cout << "CLOUD " << count << ": " << ans << "\n";
    }
}
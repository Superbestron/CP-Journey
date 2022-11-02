#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N,K; cin >> N >> K;
	if (N <= 2 && K == 0) {
		cout << 1;
		return 0;
	}
	int u = N>>1;
	int x,y,revealed=0,paired=0,ans;
	string sx,sy;
	unordered_map<string,int> m;
	unordered_set<string> s,f;
	unordered_set<int> r;
	bool last = false;
	while (K--){
		cin >> x >> y >> sx >> sy;
		if (sx == sy){
			if (s.find(sx) == s.end()){
				revealed++;
			}
			paired++;
		} else {
			if (m.find(sx) != m.end()){
				if (m.at(sx) != x && s.find(sx) == s.end()){
					revealed++;
					s.insert(sx);
				}
			} else {
				m.insert(pair<string,int>{sx,x});
			}
			if (m.find(sy) != m.end()){
				if (m.at(sy) != y && s.find(sy) == s.end()){
					revealed++;
					s.insert(sy);
				}
			} else {
				m.insert(pair<string,int>{sy,y});
			}
		}
		f.insert(sx); f.insert(sy);
		r.insert(x); r.insert(y);
	}
	if (f.size() == u || r.size() >= N-2){
		ans = u - paired;
	} else {
		ans = revealed - paired;
	}
	cout << ans;
	return 0;
}
#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    int n; cin >> n;
    int s,d,split;
    while (n--){
        cin >> s >> d;
        if (d > s || (s-d&1) == 1){
            cout << "impossible\n";
        } else {
            split = (s-d)/2;
            cout << split + d << " " << split << "\n";
        }
    }
}
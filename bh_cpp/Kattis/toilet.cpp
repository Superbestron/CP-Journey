#include<bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    char startC,c; cin >> startC >> c;
    char c1 = 'U',c2 = 'D',c3;
    int p1 = 0, p2 = 0, p3 = 0;
    if (startC != c) p1++,p2++,p3++;
    if (c != c1) p1++; if (c != c2) p2++; c3 = c;
    while(1){
        cin >> c; if (cin.eof()) break;
        if (c != c1) p1+=2; if (c != c2) p2+=2; if(c3 != c) p3++;
        c3 = c;
    }
    cout << p1 << "\n" << p2 << "\n" << p3 << "\n";
}
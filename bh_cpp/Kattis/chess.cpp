#include<bits/stdc++.h>
using namespace std;

int main(){
    int N; cin >> N;
    int x1,x2,y1,y2;
    char c1,c2;
    while(N--){
        cin >> c1 >> x2 >> c2 >> y2;
        x1 = c1 - 'A' + 1; y1 = c2 - 'A' + 1;
        string tmp;
        if (c1 == c2 && x2 == y2){
            cout << 0 << " " << c1 << " " << x2 << "\n";
            continue;
        } else if (!((x1%2 == x2%2) && (y1%2 == y2%2)) && !((x1%2 != x2%2) && (y1%2 != y2%2))){
            cout << "Impossible\n";
            continue;
        } else {
            unordered_set<string> s;
            int a,b,c,d;
            for (int i=1;i<8;i++){
                a = x1 + i; b = x1 - i; c = x2 + i; d = x2 - i;
                if (a <= 8){
                    if (c <= 8) {
                        tmp = string(1,char(a + 'A' - 1)) + " " + to_string(c);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                    if (d >= 1) {
                        tmp = string(1,char(a + 'A' - 1)) + " " + to_string(d);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                }
                if (b >= 0){
                    if (c <= 8) {
                        tmp = string(1,char(b + 'A' - 1)) + " " + to_string(c);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                    if (d >= 1) {
                        tmp = string(1,char(b + 'A' - 1)) + " " + to_string(d);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                }
                a = y1 + i; b = y1 - i; c = y2 + i; d = y2 - i;
                if (a <= 8){
                    if (c <= 8) {
                        tmp = string(1,char(a + 'A' - 1)) + " " + to_string(c);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                    if (d >= 1) {
                        tmp = string(1,char(a + 'A' - 1)) + " " + to_string(d);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                }
                if (b >= 0){
                    if (c <= 8) {
                        tmp = string(1,char(b + 'A' - 1)) + " " + to_string(c);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                    if (d >= 1) {
                        tmp = string(1,char(b + 'A' - 1)) + " " + to_string(d);
                        if (s.find(tmp) != s.end()) goto ed;
                        s.insert(tmp);
                    }
                }
            }
        }
        ed:;
        cout << 2 << " " << c1 << " " << x2 << " " << tmp << " " << c2 << " " << y2 << "\n";
    }
}

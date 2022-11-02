#include<bits/stdc++.h>
using namespace std;

const int maxH=30,maxW=30;
int m1[maxH][maxW],m2[maxH][maxW];
int main(){
    int t; cin >> t;
    while (t--){
        memset(m1,0,sizeof m1); memset(m2,0,sizeof m2);
        int w,h,n; cin >> w >> h >> n;
        int sum1=0,sum2=0; char c;
        for (int i=h-1;i>=0;i--){
            for (int j=0;j<w;j++){
                cin >> c;
                m1[i][j] = c == '#' ? 1 : 0;
                if (c == '#') sum1++;
            }
        }
        for (int i=h-1;i>=0;i--){
            for (int j=0;j<w;j++){
                cin >> c;
                m2[i][j] = c == '#' ? 1 : 0;
                if (c == '#') sum2++;
            }
        }
        int x,y;
        bool one = true;
        for (int i=0;i<n;i++){
            cin >> x >> y;
            if (one && (sum1 == 0 || sum2 == 0)){
                continue;
            } else if (one){
                if (m2[y][x] == 1){
                    m2[y][x] = 0;
                    sum2--;
                    if (sum2 == 0) one = false;
                } else {
                    one = false;
                }
            } else {
                if (m1[y][x] == 1){
                    m1[y][x] = 0;
                    sum1--;
                    if (sum1 == 0) one = true;
                } else {
                    one = true;
                }
            }
        }
        if (sum1 !=0 && sum2 == 0){
            cout << "player one wins\n";
        } else if (sum1 == 0 && sum2 !=0){
            cout << "player two wins\n";
        } else {
            cout << "draw\n";
        }
    }
}
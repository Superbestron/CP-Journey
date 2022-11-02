#include<bits/stdc++.h>
using namespace std;

const int bs = 3;
int board[bs][bs];

bool win(int val){
    int h,v,d=0,u=0;
    for (int i=0;i<bs;i++){
        if (board[i][i] == val) d++;
        if (board[bs-i-1][i] == val) u++;
        h = 0, v = 0;
        for (int j=0;j<bs;j++){
            if (board[i][j] == val) h++;
            if (board[j][i] == val) v++;
        }
        if (h==bs || v==bs) return true;
    }
    return (d==bs||u==bs);
}
int main(){
    ios::sync_with_stdio(0);
	cin.tie(0);
    int N; cin >> N;
    while (N--){
        memset(board,0,sizeof board);
        int X=0,O=0;
        char c;
        for (int i=0;i<bs;i++){
            for (int j=0;j<bs;j++){
                cin >> c;
                if (c == 'X'){
                    board[i][j] = 1;
                    X++;
                } else if (c == 'O'){
                    board[i][j] = -1;
                    O++;
                }
            }
        }
        if (O>X || abs(X-O)>1){
            cout << "no\n"; continue;
        }
        bool x = win(1); bool o = win(-1);
        cout << (o ? (x ? "no\n" : ((O==X) ?"yes\n" : "no\n")) : (x ? (X-O == 1 ? "yes\n" : "no\n") : "yes\n"));
    }
}
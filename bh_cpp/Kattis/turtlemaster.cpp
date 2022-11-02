#include<bits/stdc++.h>
using namespace std;

const int S = 8, maxI = 60;
int mx[S][S];
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
    char c;
    for (int i=S-1;i>=0;i--){
        for (int j=0;j<S;j++){
            cin >> c;
            mx[i][j] = c == 'D' ? 1 : c == 'C' ? 2 : c == 'I' ? 3 : 0;
        }
    }
    int start = maxI, x=0,y=0;
    while (true){
        cin >> c;
        if (cin.eof()) break;
        switch (c){
            case 'F':
                switch (start&3){
                    case 0:
                        y++;
                        break;
                    case 1:
                        x++;
                        break;
                    case 2:
                        y--;
                        break;
                    case 3:
                        x--;
                        break;
                }
                if (x<0 || x>7 || y<0 || y>7 || mx[x][y]>1){
                    cout << "Bug!"; return 0;
                }
                break;
            case 'L':
                start++;
                break;
            case 'R':
                start--;
                break;
            case 'X':
                int ice;
                switch (start&3){
                    case 0:
                        ice = mx[x][y+1];
                        mx[x][y+1] = 0;
                        break;
                    case 1:
                        ice = mx[x+1][y];
                        mx[x+1][y] = 0;
                        break;
                    case 2:
                        ice = mx[x][y-1];
                        mx[x][y-1] = 0;
                        break;
                    case 3:
                        ice = mx[x-1][y];
                        mx[x-1][y] = 0;
                        break;
                }
                if (ice != 3){
                    cout << "Bug!"; return 0;
                }
        }
    }
    cout << (mx[x][y] == 1 ? "Diamond!" : "Bug!");
}
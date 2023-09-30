#include<bits/stdc++.h>
#include<iostream>
#include<vector>
using namespace std;

typedef vector<vector<vector<vector<int>>>>& ez;

int square(int l, int x, int y, ez);
int vertRec(int x1, int x2, int y1, int y2, ez);

int horiRec(int x1, int x2, int y1, int y2, ez memo) {
    if (memo[x1][x2][y1][y2] != -1) return memo[x1][x2][y1][y2];
    int y = y2 - y1 + 1; int x = x2 - x1 + 1;
    int sum = 0;
    if (x > y) return vertRec(x1, x2, y1, y2, memo);
    if (x == y) return square(x, x1, y1, memo);
    if (x == 1) {
        for (int i=y1;i<=y2;i++){
            sum += memo[x1][x1][i][i];
        }
        memo[x1][x2][y1][y2] = sum;
        return sum;
    }
    int min = INT32_MAX;
    for (int i = 0; i <= y-x; i++) {
        sum += square(x, x1, y1 + i, memo);
        if (i != 0) {
            sum += horiRec(x1, x2, y1, y1 + i - 1, memo);
        }
        if (i != y - x) {
            sum += horiRec(x1, x2, y1 + i + x, y2, memo);
        }
        min = std::min(min, sum);
        if (min == 0) break;
    }
    memo[x1][x2][y1][y2] = min;
    return min;
}

int vertRec(int x1, int x2, int y1, int y2, ez memo) {
    if (memo[x1][x2][y1][y2] != -1) return memo[x1][x2][y1][y2];
    int y = y2 - y1 + 1; int x = x2 - x1 + 1;
    int sum = 0;
    if (y > x) return horiRec(x1, x2, y1, y2, memo);
    if (x == y) return square(x, x1, y1, memo);
    if (y == 1) {
        for (int i=x1;i<=x2;i++){
            sum += memo[i][i][y1][y1];
        }
        memo[x1][x2][y1][y2] = sum;
        return sum;
    }
    int min = INT32_MAX;
    for (int i = 0; i <= x-y; i++) {
        sum += square(y, x1 + i, y1, memo);
        if (i != 0) {
            sum += vertRec(x1, x1 + i - 1, y1, y2, memo);
        }
        if (i != x-y) {
            sum += vertRec(x1 + i + y, x2, y1, y2, memo);
        }
        min = std::min(min, sum);
        if (min == 0) break;
    }
    memo[x1][x2][y1][y2] = min;
    return min;
}

int square(int l, int x, int y, ez memo) {
    if (memo[x][x + l - 1][y][y + l - 1] != -1) return memo[x][x + l - 1][y][y + l - 1];
    int min = INT32_MAX;
    for (int i = 1; i < l; i++){
        min = std::min(min, square(i, x, y, memo) + square(l - i, x + i, y + i, memo)
                            + vertRec(x + i, x + l - 1, y, y + i - 1, memo) + horiRec(x, x + i - 1, y + i, y + l - 1, memo));
        if (min == 0) break;
        min = std::min(min,
                       square(i, x + l - i, y, memo) + square(l - i, x, y + i, memo) + vertRec(x, x + l - 1 - i, y, y + i - 1, memo) +
                       horiRec(x + l - i, x + l - 1, y + i, y + l - 1, memo));
        if (min == 0) break;
    }
    memo[x][x + l - 1][y][y + l - 1] = std::min(min, l);
    return memo[x][x + l - 1][y][y + l - 1];
}

int solution(vector<string> &P, int L) {
    vector<vector<vector<vector<int>>>> memo(L, vector<vector<vector<int>>>(L, vector<vector<int>>(L, vector<int>(L, L))));
    for (auto& i : memo) {
        for (auto& j : i) {
            for (auto& k : j) {
                std::fill(k.begin(), k.end(), -1);
            }
        }
    }
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            memo[i][i][j][j] = P[i][j] == '$' ? 1 : 0;
        }
    }
    return square(L, 0, 0, memo);
}

int main(){
    ios_base::sync_with_stdio(false);
    int L;
    cin >> L;
    vector<string> P(L,"");
    for(int i=0;i<L;i++){
        cin >> P[i];
    }
    cout << solution(P, L) << '\n';
    return 0;
}

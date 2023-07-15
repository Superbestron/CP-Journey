#include <bits/stdc++.h>

using namespace std;

int arr[1001][1000];
int entry_fee[1001];
int N;

int func(int x, int l) {
    if (l >= 1000) return INT32_MAX;
    if (x == N) return 0;
    if (arr[x][l] != -1) return arr[x][l];
    int forward = INT32_MAX, backward = INT32_MAX;
    if (x + l + 1 <= N) forward = entry_fee[x + l + 1] + func(x + l + 1, l + 1);
    if (x - l > 0) backward = entry_fee[x - l] + func(x - l, l);
    arr[x][l] = min(forward, backward);
    return arr[x][l];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    fill(arr[0], arr[0] + 1001 * 1000, -1);
    for (int i = 1; i <= N; i++) cin >> entry_fee[i];
    cout << func(2, 1) + entry_fee[2];
}
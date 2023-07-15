#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int K;
    unordered_map<int, int> target = {{0, 0}, {1, 1}, {2, 2}, {3, 5}, {4, 9}, {5, 8}, {6, 6}};
    while (cin >> K) {
        string answer;
        while (K != 0) {
            int remainder = K % 7;
            answer += to_string(target[remainder]);
            K -= remainder;
            K /= 7;
        }
        cout << answer << '\n';
    }
}
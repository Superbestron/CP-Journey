#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, best = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    cin >> s;
    priority_queue<string, vector<string>, greater<>> pq;
    // generate all possible cutting points
    for (int i = 0; i < s.size() - 2; i++) {
        for (int j = i + 1; j < s.size() - 1; j++) {
            string temp = s;
            reverse(temp.begin(), temp.begin() + i + 1);
            reverse(temp.begin() + i + 1, temp.begin() + j + 1);
            reverse(temp.begin() + j + 1, temp.end());
            best = min(best, temp);
        }
    }
    cout << best;
}

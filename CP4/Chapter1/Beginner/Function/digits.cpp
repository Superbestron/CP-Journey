#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string prev;
    while (cin >> prev && prev != "END") {
        int ans = 0;
        string curr;
        while (true) {
            curr = to_string(prev.size());
            ans++;
            if (prev == curr) break;
            prev = std::move(curr);
        }
        cout << ans << endl;
    }
}
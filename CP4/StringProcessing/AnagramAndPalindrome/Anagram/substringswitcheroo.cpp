#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    while (n--) {
        string A, B;
        cin >> A >> B;
        // too lazy to hash properly
        set<vector<int>> seen;
        for (int i = 0; i < B.size(); i++) {
            vector<int> freq(26);
            for (int j = i; j < B.size(); j++) {
                freq[B[j] - 'a']++;
                seen.insert(freq);
            }
        }
        int maxi_size = -1, start = -1;
        for (int i = 0; i < A.size(); i++) {
            vector<int> freq(26);
            for (int j = i; j < A.size(); j++) {
                freq[A[j] - 'a']++;
                // compare
                bool found = false;
                if (seen.count(freq)) found = true;
                // remember the int cast
                if (found && (int) (j - i + 1) > maxi_size) {
                    maxi_size = j - i + 1;
                    start = i;
                }
            }
        }
        if (maxi_size == -1) cout << "NONE\n";
        else cout << A.substr(start, maxi_size) << '\n';
    }
}
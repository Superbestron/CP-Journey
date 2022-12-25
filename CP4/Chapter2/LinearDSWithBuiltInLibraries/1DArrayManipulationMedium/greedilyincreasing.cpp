#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, c, prev = 0;
    vector<int> ans;
    cin >> n;
    while (n-- > 0) {
        cin >> c;
        if (c > prev) {
            ans.push_back(c);
            prev = c;
        }
    }
    cout << ans.size() << endl;
    for (int i : ans) {
        cout << i << ' ';
    }
}
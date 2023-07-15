#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string s;
    cin >> n;
    vector<string> ori(n), asc(n), des(n);
    for (int i = 0; i < n; i++) {
        cin >> s;
        ori[i] = asc[i] = des[i] = s;
    }
    sort(asc.begin(), asc.end());
    sort(des.begin(), des.end(), greater<>());
    if (ori == asc) cout << "INCREASING";
    else if (ori == des) cout << "DECREASING";
    else cout << "NEITHER";
}
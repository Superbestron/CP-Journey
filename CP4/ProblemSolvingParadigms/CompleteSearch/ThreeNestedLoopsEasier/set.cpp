#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string arr[12];
    for (auto& i : arr) cin >> i;
    bool empty = true;
    unordered_map<char, int> a;
    unordered_map<char, int> b;
    unordered_map<char, int> c;
    unordered_map<char, int> d;
    for (int i = 0; i < 10; i++) {
        a[arr[i][0]]++;
        b[arr[i][1]]++;
        c[arr[i][2]]++;
        d[arr[i][3]]++;
        for (int j = i + 1; j < 11; j++) {
            a[arr[j][0]]++;
            b[arr[j][1]]++;
            c[arr[j][2]]++;
            d[arr[j][3]]++;
            for (int k = j + 1; k < 12; k++) {
                a[arr[k][0]]++;
                b[arr[k][1]]++;
                c[arr[k][2]]++;
                d[arr[k][3]]++;
                if ((a.size() == 1 || a.size() == 3) && (b.size() == 1 || b.size() == 3) &&
                        (c.size() == 1 || c.size() == 3) && (d.size() == 1 || d.size() == 3)) {
                    empty = false;
                    cout << i + 1<< ' ' << j + 1 << ' ' << k + 1 << '\n';
                }
                if (!--a[arr[k][0]]) a.erase(arr[k][0]);
                if (!--b[arr[k][1]]) b.erase(arr[k][1]);
                if (!--c[arr[k][2]]) c.erase(arr[k][2]);
                if (!--d[arr[k][3]]) d.erase(arr[k][3]);
            }
            if (!--a[arr[j][0]]) a.erase(arr[j][0]);
            if (!--b[arr[j][1]]) b.erase(arr[j][1]);
            if (!--c[arr[j][2]]) c.erase(arr[j][2]);
            if (!--d[arr[j][3]]) d.erase(arr[j][3]);
        }
        if (!--a[arr[i][0]]) a.erase(arr[i][0]);
        if (!--b[arr[i][1]]) b.erase(arr[i][1]);
        if (!--c[arr[i][2]]) c.erase(arr[i][2]);
        if (!--d[arr[i][3]]) d.erase(arr[i][3]);
    }
    if (empty) cout << "no sets";
}

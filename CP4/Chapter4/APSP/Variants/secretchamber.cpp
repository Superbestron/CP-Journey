#include <bits/stdc++.h>

using namespace std;

bool AM[26][26];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    char s, d;
    string w1, w2;
    cin >> n >> m;
    for (int u = 0; u < 26; ++u) {
        for (int v = 0; v < 26; ++v) {
            AM[u][v] = false;
        }
        AM[u][u] = true;
    }
    for (int i = 0; i < n; i++) {
        cin >> s >> d;
        AM[s - 'a'][d - 'a'] = true;
    }

    for (int a = 0; a < 26; a++)                    // loop order is k->u->v
        for (int u = 0; u < 26; u++)
            for (int v = 0; v < 26; v++) {
                AM[u][v] |= (AM[u][a] & AM[a][v]);
            }

    while (m--) {
        cin >> w1 >> w2;
        if (w1.size() != w2.size()) {
            cout << "no\n";
            continue;
        }
        bool yes = true;
        for (int i = 0; i < w1.size(); i++) {
            if (!AM[w1[i] - 'a'][w2[i] - 'a']) {
                yes = false; break;
            }
        }
        if (yes) cout << "yes\n";
        else cout << "no\n";
    }
}
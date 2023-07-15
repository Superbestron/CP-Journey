#include <bits/stdc++.h>

using namespace std;

vector<string> split(string s, char delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + 1);
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s1, s2, temp, x, y;
    int n;
    while (getline(cin, s1) && getline(cin, s2)) {
        bool injective = true, surjective = false, function = true;
        unordered_set<string> domain, codomain;
        vector<string> v1 = split(s1, ' ');
        vector<string> v2 = split(s2, ' ');
        for (int i = 1; i < v2.size(); i++) codomain.insert(v2[i]);
        cin >> n;
        while (n--) {
            cin >> x >> temp >> y;
            if (domain.count(x)) function = false;
            else domain.insert(x);
            if (!codomain.count(y)) injective = false;
            else codomain.erase(y);
        }
        if (codomain.empty()) surjective = true;
        if (!function) cout << "not a function\n";
        else if (surjective && injective) cout << "bijective\n";
        else if (surjective) cout << "surjective\n";
        else if (injective) cout << "injective\n";
        else cout << "neither injective nor surjective\n";
        cin.ignore();
    }
}
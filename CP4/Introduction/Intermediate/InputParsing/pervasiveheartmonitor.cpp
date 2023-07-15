#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, word;
    while (getline(cin, s)) {
        istringstream parse(s);
        string name;
        double sum = 0;
        int count = 0;
        while (parse >> word) {
            if (!isdigit(word[0])) {
                name += word + ' ';
            } else {
                sum += stod(word);
                count++;
            }
        }
        cout << sum / count << ' ' << name << '\n';
    }
}
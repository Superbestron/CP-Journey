#include <iostream>

using namespace std;

string word_generator(int n) {
    string s;
    while (n > 0) {
        s += static_cast<char>(n % 26 + 'a');
        n /= 26;
    }
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int a, b; cin >> a >> b;
    for (int i = 1; i <= max(a, 1 + b / 2); i++) {
        cout << word_generator(i) << ' ';
    }
}
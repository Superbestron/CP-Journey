#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, val = 0;
    char b, num, suit; cin >> n >> b;
    for (int i = 0; i < 4 * n; i++) {
        cin >> num >> suit;
        if (suit == b) {
            if (num == 'A') val += 11;
            else if (num == 'K') val += 4;
            else if (num == 'Q') val += 3;
            else if (num == 'J') val += 20;
            else if (num == 'T') val += 10;
            else if (num == '9') val += 14;
            else val += 0;
        } else {
            if (num == 'A') val += 11;
            else if (num == 'K') val += 4;
            else if (num == 'Q') val += 3;
            else if (num == 'J') val += 2;
            else if (num == 'T') val += 10;
            else val += 0;
        }
    }
    cout << val;
}
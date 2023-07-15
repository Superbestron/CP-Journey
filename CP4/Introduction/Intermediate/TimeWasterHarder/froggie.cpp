#include <bits/stdc++.h>

using namespace std;

int l, w;

class car {
public:
    int offset, interval, speed;
    bool left;
};

bool squished(int x, int t, car c) {
    if (c.left) x = w - x - 1;

    // Get where the first car was
    int actualpos = c.offset + (t * c.speed);

    // Now there should be cars 'interval' apart
    while (actualpos < w) actualpos += c.interval;
    while (actualpos >= x) actualpos -= c.interval;

    // If it's stopped, check this pos, edge case
    if (c.speed == 0) return x == actualpos + c.interval;

    // Otherwise, check where it will be
    return actualpos < x && x <= actualpos + c.speed;
}

int main() {
    cin >> l >> w;
    vector<car> v;
    for (int i = 0; i < l; i++) {
        car c;
        cin >> c.offset >> c.interval >> c.speed;
        c.left = i % 2;
        v.push_back(c);
    }

    int x, y = -1;
    cin >> x;

    bool safe = true;

    string s;
    cin >> s;
    for (int t = 0; t < s.size(); t++) {
        if (s[t] == 'L') x--;
        else if (s[t] == 'R') x++;
        else if (s[t] == 'U') y++;
        else y--;

        if (y >= l) break;
        if (y >= 0 && squished(x, t, v[l - y - 1])) safe = false;
    }

    if (y < l) safe = false;
    if (safe) cout << "safe" << endl;
    else cout << "squish" << endl;
}
#include <bits/stdc++.h>

using namespace std;

class pos {
public:
    int x;
    int y;
    pos(int x, int y) : x(x), y(y) {}
};


bool is_valid(int x, int y) {
    return !(x > 8 || x < 1 || y > 8 || y < 1);
}

char c(int num) {
    return (char) num + 'A' - 1;
}

int main() {
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        char a, b;

        cin >> a;
        cin >> y1;
        cin >> b;
        cin >> y2;

        x1 = a - 'A' + 1;
        x2 = b - 'A' + 1;

        pos p1 = {x1, y1};
        pos p2 = {x2, y2};
        pos p3 = {x1, y1};

        auto hash = [](const auto& p) -> int {
            return p.x*10 + p.y;
        };
        auto equal = [](const auto& a, const auto& b) -> bool {
            return a.x == b.x && a.y == b.y;
        };
        unordered_set<pos, decltype(hash), decltype(equal)> s(0, hash, equal);

        // If they're the same
        if(p1.x == p2.x && p1.y == p2.y ) {
            cout << "0 " << a << " " << y1 << endl;
            continue;
        }

        // Get p1's possible moves
        for(int j = 1; j < 9; j++) {
            if(is_valid(p1.x + j, p1.y + j)) {
                s.emplace(p1.x+j, p1.y+j);
            }
            if(is_valid(p1.x + j, p1.y - j)) {
                s.emplace(p1.x+j, p1.y-j);
            }
            if(is_valid(p1.x - j, p1.y + j)) {
                s.emplace(p1.x-j, p1.y+j);
            }
            if(is_valid(p1.x - j, p1.y - j)) {
                s.emplace(p1.x-j, p1.y-j);
            }
        }

        // If p2 in p1's moves
        bool printed = false;
        if (s.count({p2.x, p2.y})) {
                cout << "1 " << c(p1.x) << " " << p1.y << " "
                     << c(p2.x) << " " << p2.y << endl;
                printed = true;
        }
        if(printed) {
            continue;
        }

        // Get p2's possible moves
        for(int j = 1; j < 9; j++) {
            if(is_valid(p2.x + j, p2.y + j) && s.count({p2.x+j, p2.y+j})) {
                s.emplace(p2.x+j, p2.y+j); printed = true; p3 = {p2.x+j, p2.y+j};
            }
            if(is_valid(p2.x + j, p2.y - j) && s.count({p2.x+j, p2.y-j})) {
                s.emplace(p2.x+j, p2.y-j); printed = true; p3 = {p2.x+j, p2.y-j};
            }
            if(is_valid(p2.x - j, p2.y + j) && s.count({p2.x-j, p2.y+j})) {
                s.emplace(p2.x-j, p2.y+j); printed = true; p3 = {p2.x-j, p2.y+j};
            }
            if(is_valid(p2.x - j, p2.y - j) && s.count({p2.x-j, p2.y-j})) {
                s.emplace(p2.x-j, p2.y-j); printed = true; p3 = {p2.x-j, p2.y-j};
            }
        }

        // If no shared moves
        if(!printed) {
            cout << "Impossible" << endl;
            continue;
        }

        // If a shared move
        cout << "2 " << c(p1.x)  << " " << p1.y  << " "
             << c(p3.x) << " " << p3.y << " "
             << c(p2.x)  << " " << p2.y  << endl;
    }
}
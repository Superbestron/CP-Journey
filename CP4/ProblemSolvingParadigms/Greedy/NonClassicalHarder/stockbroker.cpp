#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int d, prev = INT32_MAX, price, units = 0; cin >> d;
    long long curr = 100;
    // as long as there's dip sell,
    // else keep looking for longer increasing sequences
    bool start = true;
    while (d--) {
        cin >> price;
        // only start buying once there's a "valley"
        if (start) {
            if (price > prev) {
                start = false;
                units = min(100000LL, curr / prev);
                curr -= units * prev;
            }
        } else {
            // only sell prev and buy current if its price is lower than prev day
            if (price < prev) {
                curr += units * prev;
                units = min(100000LL, curr / price);
                curr -= units * price;
            }
        }
        prev = price;
    }
    if (units > 0) {
        curr += units * price;
    }
    cout << curr;
}
#include <iostream>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t, n, x, y; cin >> t;
    string order_type, _;
    while (t--) {
        // price, qty
        priority_queue<pair<int, int>> buy;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>>sell;
        cin >> n;
        int last_price = -1;
        while (n--) {
            int sold;
            cin >> order_type >> x >> _ >> _ >> y;
            if (order_type[0] == 'b') {
                while (x != 0 && !sell.empty() && y >= sell.top().first) {
                    pair<int, int> sell_pair = sell.top();
                    sold = min(x, sell_pair.second);
                    x -= sold;
                    last_price = sell_pair.first;
                    sell.pop();
                    // check if there are remaining quantities left to add back to pq
                    if (x == 0 && sell_pair.second - sold != 0) {
                        sell.emplace(sell_pair.first, sell_pair.second - sold);
                    }
                }
                // add extra buy orders
                if (x != 0) buy.emplace(y, x);
            } else {
                while (x != 0 && !buy.empty() && y <= buy.top().first) {
                    pair<int, int> buy_pair = buy.top();
                    sold = min(x, buy_pair.second);
                    x -= sold;
                    last_price = y;
                    buy.pop();
                    if (x == 0 && buy_pair.second - sold != 0) {
                        buy.emplace(buy_pair.first, buy_pair.second - sold);
                    }
                }
                if (x != 0) sell.emplace(y, x);
            }
            cout << (sell.empty() ? "-" : to_string(sell.top().first)) << ' '
                << (buy.empty() ? "-" : to_string(buy.top().first)) << ' '
                << (last_price == -1 ? "-" : to_string(last_price)) << endl;
        }
    }
}
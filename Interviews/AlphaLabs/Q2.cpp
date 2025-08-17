#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Order {
private:
    string id;
    string user;
    int ctr;
    int qty;
    int price;
public:
    string get_id() const {
        return id;
    }
    string get_user() const {
        return user;
    }
    int get_price() const {
        return price;
    }
    int get_time() const {
        return ctr;
    }
    int get_qty() const {
        return qty;
    }
    void dec_qty(int qty_to_dec) {
        qty -= qty_to_dec;
    }
    Order(string& id, string& user, int qty, int price, int ctr)
        : id{id}, user{user}, qty{qty}, price{price}, ctr{ctr} {}
    void print() const {
        cout << qty << '@' << price << '#' << id << ' ';
    }
};

struct buy_cmp {
    bool operator() (const Order& a, const Order& b) const {
        if (a.get_price() == b.get_price()) return a.get_time() < b.get_time();
        return a.get_price() > b.get_price();
    }
};

struct sell_cmp {
    bool operator() (const Order& a, const Order& b) const {
        if (a.get_price() == b.get_price()) return a.get_time() < b.get_time();
        return a.get_price() < b.get_price();
    }
};

class OB {
public:
    set<Order, buy_cmp> buy;
    set<Order, sell_cmp> sell;
    map<string, pair<int, int>> users;
    unordered_map<string, string> cancelled_txn; // map orderid to user
    void buy_order(Order& order, bool is_buy_order) {
        int total = 0;
        while (true) {
            if (sell.empty()) {
                // leftover orders
                if (order.get_qty() != 0 && is_buy_order) {
                    buy.insert(order);
                }
                cout << total << '\n';
                return;
            }
            Order curr = *sell.begin();
            // lazy erase
            if (cancelled_txn.count(curr.get_id())) {
                string owner = cancelled_txn[curr.get_id()];
                // can delete
                if (curr.get_user() == owner) {
                    sell.erase(curr);
                } else {
                    cancelled_txn.erase(curr.get_id());
                }
                continue;
            }
            if (is_buy_order && curr.get_price() > order.get_price()) {
                if (order.get_qty() != 0) {
                    buy.insert(order);
                }
                cout << total << '\n';
                return;
            }
            sell.erase(sell.begin());
            int qty_to_dec = min(order.get_qty(), curr.get_qty());
            order.dec_qty(qty_to_dec);
            curr.dec_qty(qty_to_dec);
            int val = qty_to_dec * curr.get_price();
            total += val;
            // do the maker-taker calculations
            users[curr.get_user()].first += val;
            // taker
            users[order.get_user()].second += val;
            // qty_left == 0
            if (curr.get_qty() != 0) {
                sell.insert(curr);
                cout << total << '\n';
                return;
            }
        }
    }
    void sell_order(Order& order, bool is_buy_order) {
        int total = 0;
        while (true) {
            if (buy.empty()) {
                if (order.get_qty() != 0 && is_buy_order) {
                    sell.insert(order);
                }
                cout << total << '\n';
                return;
            }
            Order curr = *buy.begin();
            // lazy erase
            if (cancelled_txn.count(curr.get_id())) {
                string owner = cancelled_txn[curr.get_id()];
                // can delete
                if (curr.get_user() == owner) {
                    buy.erase(curr);
                } else {
                    cancelled_txn.erase(curr.get_id());
                }
                continue;
            }
            if (is_buy_order && curr.get_price() < order.get_price()) {
                if (order.get_qty() != 0) {
                    sell.insert(order);
                }
                cout << total << '\n';
                return;
            }
            buy.erase(buy.begin());
            int qty_to_dec = min(order.get_qty(), curr.get_qty());
            order.dec_qty(qty_to_dec);
            curr.dec_qty(qty_to_dec);
            int val = qty_to_dec * curr.get_price();
            total += val;
            // do the maker-taker calculations
            users[curr.get_user()].first += val;
            // taker
            users[order.get_user()].second += val;
            // qty_left == 0
            if (curr.get_qty() != 0) {
                buy.insert(curr);
                cout << total << '\n';
                return;
            }
        }
    }
    void cancel(string& id, string& user) {
        cancelled_txn[id] = user;
    }
    void print() {
        cout << "B: ";
        for (const Order& s : buy) if (!cancelled_txn.count(s.get_id())) s.print();
        cout << "\nS: ";
        for (const Order& s : sell) if (!cancelled_txn.count(s.get_id())) s.print();
        cout << '\n';
        for (auto& p : users) {
            cout << p.first << '-' << p.second.first << '-' << p.second.second << '\n';
        }
    }
};

vector<string> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    if (s.empty()) return arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.emplace_back(s);
    return arr;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print here_comes_santa_claus_validation_output.txt to STDOUT */
    string s, user;
    OB ob;
    int ctr = 0, users;
    cin >> users;
    while (users--) {
        cin >> user;
        pair<int, int> p = make_pair(0, 0);
        ob.users[user] = p;
    }
    cin.ignore();
    while (getline(cin, s)) {
        if (s == "END") break;
        vector<string> v = split(s, " ");
        if (v[0] == "SUB") {
            if (ob.users.count(v[2]) == 0) continue;
            if (v[1] == "LO") {
                Order temp(v[4], v[2], stoi(v[5]), stoi(v[6]), ctr);
                if (v[3] == "B") {
                    ob.buy_order(temp, true);
                } else {
                    ob.sell_order(temp, true);
                }
            } else {
                Order temp(v[4], v[2], stoi(v[5]), 0, ctr);
                if (v[3] == "B") {
                    ob.buy_order(temp, false);
                } else {
                    ob.sell_order(temp, false);
                }
            }
        } else {
            ob.cancel(v[2], v[1]);
        }
        ctr++;
    }
    ob.print();
    return 0;
}
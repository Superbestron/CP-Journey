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
public:
    string id;
    int ctr;
    int qty;
    int price;
    Order(string& id, int qty, int price, int ctr) : id{id}, qty{qty}, price{price}, ctr{ctr} {}
    void print() const {
        cout << qty << '@' << price << '#' << id << ' ';
    }
};

struct compare {
    bool operator() (const Order& a, const Order& b) const {
        if (a.price == b.price) return a.ctr < b.ctr;
        return a.price > b.price;
    }
};

struct compare2 {
    bool operator() (const Order& a, const Order& b) const {
        if (a.price == b.price) return a.ctr < b.ctr;
        return a.price < b.price;
    }
};

class OB {
public:
    set<Order, compare> buy;
    set<Order, compare2> sell;
    unordered_set<string> forbidden;
    void lo_b(Order& order, bool is_buy_order) {
        int total = 0;
        while (true) {
            if (sell.empty()) {
                if (order.qty != 0 && is_buy_order) {
                    buy.insert(order);
                }
                cout << total << '\n';
                return;
            }
            Order curr = *sell.begin();
            // lazy erase
            if (forbidden.count(curr.id)) {
                sell.erase(curr);
                continue;
            }
            if (is_buy_order && curr.price > order.price) {
                if (order.qty != 0) {
                    buy.insert(order);
                }
                cout << total << '\n';
                return;
            }
            sell.erase(sell.begin());
            int qty_to_dec = min(order.qty, curr.qty);
            order.qty -= qty_to_dec;
            curr.qty -= qty_to_dec;
            total += qty_to_dec * curr.price;
            // qty_left == 0
            if (curr.qty != 0) {
                sell.insert(curr);
                cout << total << '\n';
                return;
            }
        }
    }
    void lo_s(Order& order, bool is_buy_order) {
        int total = 0;
        while (true) {
            if (buy.empty()) {
                if (order.qty != 0 && is_buy_order) {
                    sell.insert(order);
                }
                cout << total << '\n';
                return;
            }
            Order curr = *buy.begin();
            // lazy erase
            if (forbidden.count(curr.id)) {
                buy.erase(curr);
                continue;
            }
            if (is_buy_order && curr.price < order.price) {
                if (order.qty != 0) {
                    sell.insert(order);
                }
                cout << total << '\n';
                return;
            }
            buy.erase(buy.begin());
            int qty_to_dec = min(order.qty, curr.qty);
            order.qty -= qty_to_dec;
            curr.qty -= qty_to_dec;
            total += qty_to_dec * curr.price;
            // qty_left == 0
            if (curr.qty != 0) {
                buy.insert(curr);
                cout << total << '\n';
                return;
            }
        }
    }
    void cancel(string& id) {
        forbidden.insert(id);
    }
    void print() {
        cout << "B: ";
        for (const Order& s : buy) if (!forbidden.count(s.id)) s.print();
        cout << "\nS: ";
        for (const Order& s : sell) if (!forbidden.count(s.id)) s.print();
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
    string s;
    OB ob;
    int ctr = 0;
    while (getline(cin, s)) {
        if (s == "END") break;
        vector<string> v = split(s, " ");
        if (v[0] == "SUB") {
            if (v[1] == "LO") {
                Order temp(v[3], stoi(v[4]), stoi(v[5]), ctr);
                if (v[2] == "B") {
                    ob.lo_b(temp, true);
                } else {
                    ob.lo_s(temp, true);
                }
            } else {
                Order temp(v[3], stoi(v[4]), 0, ctr);
                if (v[2] == "B") {
                    ob.lo_b(temp, false);
                } else {
                    ob.lo_s(temp, false);
                }
            }
        } else {
            ob.cancel(v[1]);
        }
        ctr++;
    }
    ob.print();
    return 0;
}
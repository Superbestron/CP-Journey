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
#include <utility>
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
#include <memory>

using namespace std;

vector<string> split(string& s, char delimiter) {
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

class Order {
private:
    string price;
    int id; // sequence id
    long long orderId;
    double qty;
public:
    string getPrice() const {
        return price;
    }
    int getId() const {
        return id;
    }
    long long getOrderId() const {
        return orderId;
    };

    Order() {}

    Order(string price, int id, long long orderId, double qty)
            : price(std::move(price)), id(id), orderId(orderId), qty(qty) {}

    Order(const Order& other) : price(other.price), id(other.id), orderId(other.orderId), qty(other.qty) {}

    Order& operator=(const Order& other) {
        if (this == &other) {
            return *this;
        }
        this->price = other.price;
        this->id = other.id;
        this->orderId = other.orderId;
        this->qty = other.qty;
        return *this;
    }

    Order(Order&& other) : price(std::move(other.price)), id(other.id), orderId(other.orderId), qty(other.qty) {}

    Order& operator=(Order&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        this->price = other.price;
        this->id = other.id;
        this->orderId = other.orderId;
        this->qty = other.qty;
        return *this;
    }
};

struct SellsCompare {
    bool operator() (const std::shared_ptr<Order>& o1, const std::shared_ptr<Order>& o2) const {
        string t1 = o1->getPrice();
        string t2 = o2->getPrice();
        double result1 = std::stod(t1);
        double result2 = std::stod(t2);
        if (abs(result1 - result2) < 1e-9) {
            return o1->getId() < o2->getId();
        }
        return result1 > result2;
    }
};

struct BuysCompare {
    bool operator() (const std::shared_ptr<Order>& o1, const std::shared_ptr<Order>& o2) const {
        string t1 = o1->getPrice();
        string t2 = o2->getPrice();
        double result1 = std::stod(t1);
        double result2 = std::stod(t2);
        if (abs(result1 - result2) < 1e-9) {
            return o1->getId() < o2->getId();
        }
        return result1 < result2;

    }
};

int main() {
    /* Enter your code here. Read input from STDIN. Print here_comes_santa_claus_validation_output.txt to STDOUT */
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    // price, seq, orderID, qty
    priority_queue<std::shared_ptr<Order>, vector<std::shared_ptr<Order>>, SellsCompare> sells;
    unordered_map<long long, std::shared_ptr<Order>> id_map;
    unordered_set<long long> to_delete;
    priority_queue<std::shared_ptr<Order>, vector<std::shared_ptr<Order>>, BuysCompare> buys;
    int id = 0;
    while (getline(cin, s)) {
        vector<string> v(split(s, ' '));
        if (v[0] == "END") {
            break;
        }
        if (v[0] == "O") {
            string best_sells = "0";
            string best_buys = "0";
            // if to_delete
            while (!sells.empty() && to_delete.count(sells.top()->getOrderId())) {
                to_delete.erase(sells.top()->getOrderId());
                id_map.erase(sells.top()->getOrderId());
                sells.pop();
            }
            if (!sells.empty()) {
                best_sells = sells.top()->getPrice();
            }
            while (!buys.empty() && to_delete.count(buys.top()->getOrderId())) {
                to_delete.erase(buys.top()->getOrderId());
                id_map.erase(buys.top()->getOrderId());
                buys.pop();
            }
            if (!buys.empty()) {
                best_buys = buys.top()->getPrice();
            }
            printf("(%s, %s)\n", best_buys.c_str(), best_sells.c_str());
        } else if (v[0] == "S") {
            std::shared_ptr o = std::make_shared<Order>(v[3], id++, stoll(v[1]), stod(v[2]));
            sells.push(o);
            id_map[stoll(v[1])] = std::move(o);

        } else if (v[0] == "B") {
            std::shared_ptr o = std::make_shared<Order>(v[3], id++, stoll(v[1]), stod(v[2]));
            buys.push(o);
            id_map[stoll(v[1])] = std::move(o);
        } else {
            if (id_map.count(stoll(v[1]))) {
                to_delete.insert(stoll(v[1]));
            }
        }
    }
}

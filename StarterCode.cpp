#include <bits/stdc++.h>

using namespace std;

bool check_date(int day, int month, int year) {
    if (day == 0 || month == 0) return false;
    if (month > 12) return false;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        if (day > 31) return false;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        if (day > 30) return false;
    } else {
        bool leap;
        if (year % 400 == 0) {
            leap = true;
        } else if (year % 100 == 0) {
            leap = false;
        } else if (year % 4 == 0) {
            leap = true;
        } else {
            leap = false;
        }
        if (leap) {
            if (day > 29) return false;
        } else {
            if (day > 28) return false;
        }
    }
//    earliest += string(2 - min(2, (int) to_string(day).length()), '0') + to_string(day) + " "
//                + string(2 - min(2, (int) to_string(month).length()), '0') + to_string(month) + " "
//                + string(4 - min(4, (int) to_string(year).length()), '0') + to_string(year);
    return true;
}

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

class Compare {
public:
    bool operator() (const pair<int, int>& o1, const pair<int, int> o2) const {
        return o1.first == o2.first;
    }
};
class Compare2 {
public:
    bool operator() (const pair<int, int>& o1, const pair<int, int> o2) const {
        return o1.first < o2.first;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    vector<string> v = split("Hello World!", ' ');

    auto comp = [](auto& a, auto& b ) { return a.second > b.second; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq2;
    set<pair<int, int>, decltype(comp)> s(comp);
    set<pair<int, int>, Compare2> s2;
    s.insert(make_pair(1,2));
    s2.insert(make_pair(1, 2));
    pq.emplace(1,2);
    pq2.emplace(1, 2);
}

// Fast exponentiation
long long fexp(long long b, long long p, long long mod){
    if (p == 0) return 1;
    if (p == 1) return b;

    if (p & 1) {
        return (((fexp(b, p >> 1, mod) * fexp(b, p >> 1, mod)) % mod) * b) % mod;
    } else{
        return (fexp(b, p >> 1, mod) * fexp(b, p >> 1, mod)) % mod;
    }
}

// Important points
// 1. String comparison
// if s1 and s2 is std::string
// s1 < s2 is by ascii ("dad" < "mom") == true
// else if s1 and s2 are char*/char[]
// s1 < s2 is by lexicographical order ("dad" < "mom") == false
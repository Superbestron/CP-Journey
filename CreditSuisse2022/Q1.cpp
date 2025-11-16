#include <bits/stdc++.h>
using namespace std;

string solution(long n) {
    // Write solution here
    if (n % 4 == 0) return "BUY";
    else if (n % 2 == 0) return "PASS";
    else return "SELL";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    long n;
    cin >> n;
    cout << solution(n) << '\n';
}

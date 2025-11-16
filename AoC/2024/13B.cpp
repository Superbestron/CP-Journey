#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Some math knowledge is handy here. No need for any crazy math i.e. CRT, but just use what you've learnt in linear
// algebra i.e. Cramer's rule to solve the simultaneous equations. It can even be solved more simply using high-school
// level math because it's essentially just finding the intersection of 2 lines. Of course, there might be an infinite
// or no number of solutions which correspond to parallel lines which are the same line or different lines respectively,
// but the test case doesn't cover them.

pair<int, int> parse(string& s) {
    vector<string> t = split(s, ':');
    vector<string> t2 = split(t[1], ',');
    int a1 = stoi(split(t2[0], '+')[1]);
    int a2 = stoi(split(t2[1], '+')[1]);
    return {a1, a2};
}

ll solve_system_integer(ll a, ll b, ll c, ll d, ll e, ll f) {
    ll D = (a * e) - (b * d); // Calculate the main determinant D

    // Calculate the numerators for x and y using Cramer's rule logic
    ll Nx = (c * e) - (b * f);
    ll Ny = (a * f) - (c * d);

    cout << "For the system:\n";
    cout << a << "x + " << b << "y = " << c << "\n";
    cout << d << "x + " << e << "y = " << f << "\n\n";

    if (D == 0) {
        // Determinant is zero, lines are parallel or coincident
        if (Nx == 0 && Ny == 0) cout << "Infinitely many rational solutions (lines are coincident).\n";
        else cout << "No solutions exist at all (lines are parallel and distinct).\n";
    } else {
        cout << "A unique rational solution exists.\n";
        cout << "x = " << Nx << "/" << D << "\n";
        cout << "y = " << Ny << "/" << D << "\n";

        if (Nx % D == 0 && Ny % D == 0) {
            ll x = Nx / D;
            ll y = Ny / D;
            cout << "\n✅ The unique solution is an integer solution: (x, y) = (" << x << ", " << y << ").\n";

            if (x >= 0 && y >= 0) {
                cout << "✅ The integer solution is non-negative.\n";
                return Nx / D * 3 + Ny / D;
            } else {
                cout << "❌ The integer solution is negative in one or both components.\n";
            }
        } else {
            cout << "\n❌ The unique solution is not an integer solution (it involves fractions).\n";
            cout << "Therefore, no non-negative integer solutions exist.\n";
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    ll ans = 0;
    vector<string> grid;
    while (getline(cin, s)) {
        auto [a1, a2] = parse(s);
        getline(cin, s);
        auto [b1, b2] = parse(s);
        getline(cin, s);
        vector<string> t = split(s, ':');
        vector<string> t2 = split(t[1], ',');
        ll p1 = stoi(split(t2[0], '=')[1]) + 10000000000000;
        ll p2 = stoi(split(t2[1], '=')[1]) + 10000000000000;
        ans += solve_system_integer(a1, b1, p1, a2, b2, p2);
        getline(cin, s);
    };
    cout << ans << '\n';
}

#include <iostream>
#include <vector>

using namespace std;

int solve(vector<int> a, vector<int> b) {
    int a_ctr = 0, b_ctr = 100, worst = 0;
    while (true) {
        while (a[a_ctr] == 0) {
            a_ctr++;
            if (a_ctr > 100) goto end;
        }
        while (b[b_ctr] == 0) {
            b_ctr--;
            if (b_ctr < 0) goto end;
        }
        worst = max(worst, a_ctr + b_ctr);
        // speed up calc
        int m = min(a[a_ctr], b[b_ctr]);
        a[a_ctr] -= m;
        b[b_ctr] -= m;
    }
    end:
    return worst;
}

int main() {
    int n, val;
    cin >> n;
    vector<int> a(101, 0), b(101, 0);
    for (int ctr = 0; ctr < n; ctr++) {
        cin >> val;
        a[val]++;
        cin >> val;
        b[val]++;
        cout << solve(a, b) << endl;
    }
}
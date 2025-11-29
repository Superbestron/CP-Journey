#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Implement as it is

ll combo_ope(vll& regs, ll ope) {
    if (ope <= 3) return ope;
    else return regs[ope - 4];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s, output;
    vll regs, inst;
    int idx = 0;
    while (getline(cin, s)) {
        if (idx < 3) {
            vector<string> v = split(s, ' ');
            regs.push_back(stoll(v[2]));
        } else if (idx == 4) {
            vector<string> v = split(s, ' ');
            vector<string> nums(split(v[1], ','));
            for (auto& ss : nums) inst.push_back(stoll(ss));
            for (int i = 0; i < inst.size();) {
                ll op = inst[i];
                ll ope = inst[i + 1];
                if (op == 0) {
                    ll temp = pow(2, combo_ope(regs, ope));
                    regs[0] /= temp;
                } else if (op == 1) regs[1] ^= ope;
                else if (op == 2) regs[1] = combo_ope(regs, ope) & 0b111;
                else if (op == 3) {
                    if (regs[0] != 0) {
                        i = ope;
                        continue;
                    }
                } else if (op == 4) regs[1] ^= regs[2];
                else if (op == 5) {
                    output += to_string(combo_ope(regs, ope) & 0b111);
                    output.push_back(',');
                } else if (op == 6) {
                    ll temp = pow(2, combo_ope(regs, ope));
                    regs[1] = regs[0] / temp;
                } else {
                    ll temp = pow(2, combo_ope(regs, ope));
                    regs[2] = regs[0] / temp;
                }
                i += 2;
            }
        }
        idx++;
    }
    if (!output.empty()) output.pop_back();
    cout << output << '\n';
}

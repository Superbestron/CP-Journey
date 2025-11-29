#include <bits/stdc++.h>
#include "../../Libraries/Miscellaneous.cpp"
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// Very tricky non-conventional question which I admit that I had to to resort to scrolling through reddit to get some
// hints. I gathered that we need to observe the pattern carefully and do a "intelligent" brute-force. I was too caught
// up in finding an elegant and tractable solution which didn't seem to exist. if you observe carefully, you'll notice
// that at every iteration of the program loop while executing the instruction, only A's lower 3 bits are used and
// discarded, while the initial values of B and C don't matter at all. This means that the last 3 bits will generate
// the last output of the program, and the next last 3 bits will generate the 2nd last output of the program and etc.
// With this in mind, it boils down to working backwards and trying each group of 3 bits at the time to see if it's able
// to generate the required output character. The technique used here is recursive backtracking which is done using DFS. Use 17A
// as a subroute to simulate the program.

int combo_ope(vll& regs, int ope) {
    if (ope <= 3) return ope;
    else return regs[ope - 4];
}

string simulate_program(vi& inst, vll& regs) {
    string output;
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
        } else if (op == 6) {
            ll temp = pow(2, combo_ope(regs, ope));
            regs[1] = regs[0] / temp;
        } else {
            ll temp = pow(2, combo_ope(regs, ope));
            regs[2] = regs[0] / temp;
        }
        i += 2;
    }
    reverse(output.begin(), output.end());
    return output;
}

bool dfs(vi& inst, string& expected, string curr_bin, int idx) {
    if (idx == expected.size()) {
        cout << stoll(curr_bin, nullptr, 2) << '\n';
        return true;
    }
    for (int i = 0; i < 8; i++) {
        string binary_string = curr_bin + bitset<3>(i).to_string();
        ll new_num = stoll(binary_string, nullptr, 2);
        vll regs(3);
        regs[0] = new_num;
        string output = simulate_program(inst, regs);
        if (expected.substr(0, idx + 1) == output) {
            if (dfs(inst, expected, binary_string, idx + 1)) return true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    vi inst;
    int idx = 0;
    while (getline(cin, s)) {
        if (idx == 4) {
            vector<string> v = split(s, ' ');
            vector<string> nums(split(v[1], ','));
            string expected;
            for (auto& ss : nums) {
                inst.push_back(stoll(ss));
                expected += ss;
            }
            reverse(expected.begin(), expected.end()); // only numbers inside
            assert(dfs(inst, expected, "", 0));
        }
        idx++;
    }
}

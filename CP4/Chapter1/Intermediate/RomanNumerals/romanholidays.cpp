#include <bits/stdc++.h>

using namespace std;

// The number ordering is difficult...
// C.....M,MC...MM     ,MMC..............INF.........MMV.....MMXXXVIII, MV,...,MXXXVIII, V... XXXVIII

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    unordered_map<int, string> ones = {{0, ""}, {1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"},
                                       {7, "VII"}, {8, "VIII"}, {9, "IX"}};
    unordered_map<int, string> tens = {{0, ""}, {10, "X"}, {20, "XX"}, {30, "XXX"}, {40, "XL"}, {50, "L"}, {60, "LX"},
                                       {70, "LXX"}, {80, "LXXX"}, {90, "XC"}};
    unordered_map<int, string> hundreds = {{0, ""}, {100, "C"}, {200, "CC"}, {300, "CCC"}, {400, "CD"}, {500, "D"},
                                            {600, "DC"}, {700, "DCC"}, {800, "DCCC"}, {900, "CM"}};

    unordered_map<int, string> arab_rom_thousand;
    map<string, int> rom_arab_thousand;
    for (auto& [hundred_arab, hundred_rom]: hundreds) {
        for (auto& [ten_arab, ten_rom]: tens) {
            for (auto& [one_arab, one_rom]: ones) {
                if (hundred_arab + ten_arab + one_arab == 0) continue;
                arab_rom_thousand[hundred_arab + ten_arab + one_arab] = hundred_rom + ten_rom + one_rom;
                rom_arab_thousand[hundred_rom + ten_rom + one_rom] = hundred_arab + ten_arab + one_arab;
            }
        }
    }
    arab_rom_thousand[1000] = "M";
    rom_arab_thousand["M"] = 1000;

    int n, input; cin >> n;
    while (n--) {
        cin >> input;
        int a_000 = input % 1000, a_thousands = input / 1000;

        if (a_000 == 0) {
            cout << a_thousands * 946 << '\n'; // edge case
            continue;
        }

        int ans = 0, index = 0;
        string a_000_rom = arab_rom_thousand[a_000];
        if (a_000_rom[0] != 'V' && a_000_rom[0] != 'X') {
            for (auto& [key, val] : rom_arab_thousand) {
                if (key == a_000_rom) {
                    ans = index + 1;
                    ans += 946 * a_thousands;
                    break;
                }
                index++;
            }
        } else {
            for (auto& [key, val] : rom_arab_thousand) {
                if (key == a_000_rom) {
                    ans = index - 1000;
                    ans += (-54) * a_thousands;
                }
                index++;
            }
        }
        cout << ans << '\n';
    }
}

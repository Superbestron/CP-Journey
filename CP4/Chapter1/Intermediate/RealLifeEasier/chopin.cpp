#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int ctr = 1;
    unordered_map<string, string> m = {{"A#", "Bb"}, {"Bb", "A#"}, {"C#", "Db"},
                                       {"Db", "C#"}, {"D#", "Eb"}, {"Eb", "D#"},
                                       {"F#", "Gb"}, {"Gb", "F#"}, {"G#", "Ab"},
                                       {"Ab", "G#"}};
    string note, tonality;
    while (cin >> note >> tonality) {
        if (m.count(note) == 0) cout << "Case " << ctr << ": " << "UNIQUE" << endl;
        else cout << "Case " << ctr << ": " << m[note] << ' ' << tonality << endl;
        ctr++;
    }
}
#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int arr[26], time, solved = 0, penalty = 0;
    memset(arr, 0, sizeof arr);
    char problem;
    string answer;
    while (cin >> time && time != -1) {
        cin >> problem >> answer;
        if (arr[problem - 'A'] == -1) continue;
        if (answer[0] == 'r') {
            solved++;
            penalty += time + arr[problem - 'A'];
            arr[problem - 'A'] = -1;
        } else {
            arr[problem - 'A'] += 20;
        }
    }
    cout << solved << ' ' << penalty;
}
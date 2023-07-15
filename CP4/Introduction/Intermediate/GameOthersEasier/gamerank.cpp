#include <iostream>

using namespace std;

int get_stars(int rank) {
    if (rank <= 10) return 5;
    else if (rank <= 15) return 4;
    else if (rank <= 20) return 3;
    else return 2;
}

void add_stars(int& rank, int& curr_stars) {
    if (curr_stars == get_stars(rank)) {
        curr_stars = 0;
        rank--;
    }
    curr_stars++;
}

void lose_stars(int& rank, int& curr_stars) {
    if (rank == 20) {
        if (curr_stars > 0) curr_stars--;
    } else if (rank < 20) {
        if (curr_stars == 0) {
            rank++;
            curr_stars = get_stars(rank) - 1;
        } else {
            curr_stars--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string s; cin >> s;
    int streak = 0, rank = 25, curr_stars = 0;
    for (char c : s) {
        if (c == 'W') {
            streak++;
            if (rank >= 6 && streak >= 3) add_stars(rank, curr_stars);
            if (rank == 0) {
                cout << "Legend"; return 0;
            }
            add_stars(rank, curr_stars);
            if (rank == 0) {
                cout << "Legend"; return 0;
            }
        } else {
            streak = 0;
            lose_stars(rank, curr_stars);
        }
    }
    cout << rank;
}
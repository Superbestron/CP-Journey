//#include <bits/stdc++.h>
//using namespace std;
//
//int N, OK, ctr = 0;
//bool four = false;
//string arr[4];
//pair<pair<int, int>, pair<int, int>> coords[4];
//vector<bool> seen(4);
//unordered_map<int, pair<int, int>> int_to_coords;
//int directions[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
//vector<vector<int>>
//
//int dp(int u) {
//
//}
//
//void backtrack(int u) {
//    if (u == ctr) {
//        // process
//
//    }
//    auto& [i, j] = int_to_coords[u];
//    arr[i][j] = 'R'; backtrack(u + 1);
//    arr[i][j] = 'G'; backtrack(u + 1);
//    arr[i][j] = 'B'; backtrack(u + 1);
//    if (four) arr[i][j] = 'Y'; backtrack(u + 1);
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    for (int i = 0; i < 4; i++) {
//        cin >> arr[i];
//        for (int j = 0; j < 4; j++) {
//            if (arr[i][j] == 'R') {
//                if (seen[0]) coords[0].second = make_pair(i, j);
//                else {
//                    coords[0].first = make_pair(i, j);
//                    seen[0] = true;
//                }
//            } else if (arr[i][j] == 'G') {
//                if (seen[1]) coords[1].second = make_pair(i, j);
//                else {
//                    coords[1].first = make_pair(i, j);
//                    seen[1] = true;
//                }
//            } else if (arr[i][j] == 'B') {
//                if (seen[2]) coords[2].second = make_pair(i, j);
//                else {
//                    coords[2].first = make_pair(i, j);
//                    seen[2] = true;
//                }
//            } else if (arr[i][j] == 'Y') {
//                four = true;
//                if (seen[3]) coords[3].second = make_pair(i, j);
//                else {
//                    coords[3].first = make_pair(i, j);
//                    seen[3] = true;
//                }
//            } else {
//                int_to_coords[ctr++] = std::move(make_pair(i, j));
//            }
//        }
//    }
//}
//

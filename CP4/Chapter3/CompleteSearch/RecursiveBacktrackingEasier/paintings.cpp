//#include <iostream>
//#include <vector>
//#include <unordered_set>
//
//using namespace std;
//
//vector<vector<string>> recurse(vector<vector<string>>& output, unordered_set<string>& s) {
//    if (s.empty()) return output;
//    cout << "hi";
//    unordered_set<string> temp(s);
//    vector<vector<string>> ans;
//    for (auto& str : temp) {
//        vector<vector<string>> v = output;
//        for (auto& i : v) {
//            i.push_back(str);
//        }
//        s.erase(str);
//        vector<vector<string>> t1 = recurse(v, s);
//        ans.insert(ans.end(), v.begin(), v.begin());
//        s.insert(str);
//    }
//    return ans;
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    int t, n, m;
//    string temp;
//    cin >> t;
//    while (t-- > 0) {
//        cin >> n;
//        unordered_set<string> v;
//        for (int i = 0; i < n; i++) {
//            cin >> temp;
//            v.insert(temp);
//        }
//        cin >> m;
//        vector<pair<int, int>> pairs(m);
//        for (int i = 0; i < m; i++) {
//            pair<int, int> p;
//            cin >> p.first >> p.second;
//            pairs.emplace_back(p);
//        }
//        vector<vector<string>> output;
//        vector<string> t1;
//        output.emplace_back(t1);
//        output = recurse(output, v);
//        for (auto& i : output) {
//            for (auto& j : i) {
//                cout << j << ' ';
//            }
//            cout << endl;
//        }
//    }
//}

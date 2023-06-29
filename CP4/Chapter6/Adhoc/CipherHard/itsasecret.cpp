//#include <bits/stdc++.h>
//
//using namespace std;
//
//void to_upper(string& str) {
//    for (char& c : str) toupper(c);
//}
//
//int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr);
//    int n;
//    char arr[5][5];
//    string key, word;
//    while (cin >> n && n != 0) {
//        cin >> key;
//        to_upper(key);
//        int ctr = 0;
//        for (; ctr < key.size(); ctr++) {
//            arr[ctr / 5][ctr % 5] = key[ctr];
//        }
//        for (int ltr = 'A'; ctr < 25; ltr++, ctr++) {
//            arr[ctr / 5][ctr % 5] = key[ltr];
//        }
//        for (int i = 0; i < n; i++) {
//            vector<string> digraphs;
//            cin >> word;
//            to_upper(word);
//            for (int j = 0; j < n; j++) {}
//
//        }
//    }
//}
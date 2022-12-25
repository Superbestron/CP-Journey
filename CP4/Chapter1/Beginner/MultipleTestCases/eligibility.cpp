#include <iostream>
#include <vector>

using namespace std;

vector<string> split(string s, const string& delimiter) {
    size_t pos;
    string token;
    vector<string> arr;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        arr.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.push_back(s);
    return arr;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, s4;
    string s1, s2, s3;
    cin >> n;
    while (n-- > 0) {
        cin >> s1 >> s2 >> s3 >> s4;
        cout << s1 << ' ';
        vector<string> s2_parse = split(s2, "/");
        vector<string> s3_parse = split(s3, "/");
        if (stoi(s2_parse[0]) >= 2010 || stoi(s3_parse[0]) >= 1991) cout << "eligible";
        else if (s4 >= 41) cout << "ineligible";
        else cout << "coach petitions";
        cout << endl;
    }
}
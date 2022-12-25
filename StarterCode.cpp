//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//vector<string> split(string s, const string& delimiter) {
//    size_t pos;
//    string token;
//    vector<string> arr;
//    if (s.empty()) return arr;
//    while ((pos = s.find(delimiter)) != string::npos) {
//        token = s.substr(0, pos);
//        arr.emplace_back(token);
//        s.erase(0, pos + delimiter.length());
//    }
//    arr.emplace_back(s);
//    return arr;
//}
//
//int main() {
//    vector<string> v = split("Hello World!", " ");
//};

// Important points
// 1. String comparison
// if s1 and s2 is std::string
// s1 < s2 is by ascii ("dad" < "mom") == true
// else if s1 and s2 are char*/char[]
// s1 < s2 is by lexicographical order ("dad" < "mom") == false
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);

    int N, K, ans = 0, potential = 0;
    cin>>N>>K;
    unordered_map<string, unordered_set<int>> map;
    while (K-- > 0) {
        int first, second;
        string s1, s2;
        cin>>first>>second>>s1>>s2;
        map[s1].insert(first);
        map[s2].insert(second);
        // if both same cards, means alr taken
        if (s1 == s2) ans--;
    }
    for (auto& [key, value] : map) {
        if (value.size() == 2) ans++;
        else potential++;
    }
    // if all cards taken at least once, can know the rest
    if (map.size() == N / 2) ans += potential;
    else if (map.size() == (N / 2) - 1 && potential == 0) ans++;
    cout << ans;
}
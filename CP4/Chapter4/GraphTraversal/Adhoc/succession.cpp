#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> AL(100, vector<int>());
unordered_map<string, int> person_to_int;
unordered_map<int, string> int_to_person;
vector<int> claimants, in_degree(100, 0);
vector<double> memo(100, 0);
int N, M, founder_no, person_ctr = 0;

inline void add_to_map(string& person) {
    if (person_to_int.count(person) == 0) {
        person_to_int[person] = person_ctr;
        int_to_person[person_ctr++] = person;
    }
}

double dfs(int u) {
    if (u == founder_no) return 1 << 10;
    double& ans = memo[u];
    if (ans != 0) return ans;
    double blood = 0;
    for (int v : AL[u]) blood += dfs(v);
    return ans = blood / 2;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    string founder, child, parent1, parent2, claimant;
    cin >> N >> M >> founder;
    add_to_map(founder);
    founder_no = person_to_int[founder];
    while (N--) {
        cin >> child >> parent1 >> parent2;
        add_to_map(child);
        add_to_map(parent1);
        add_to_map(parent2);
        AL[person_to_int[child]].push_back(person_to_int[parent1]);
        in_degree[person_to_int[parent1]]++;
        AL[person_to_int[child]].push_back(person_to_int[parent2]);
        in_degree[person_to_int[parent2]]++;
    }
    while (M--) {
        cin >> claimant;
        add_to_map(claimant);
        claimants.push_back(person_to_int[claimant]);
    }

    for (int i = 0; i < person_ctr; i++) {
        if (in_degree[i] == 0) dfs(i);
    }

    int max_id;
    double maxi = -1;
    for (int i : claimants) {
        if (memo[i] > maxi) {
            maxi = memo[i];
            max_id = i;
        }
    }

    cout << int_to_person[max_id];
}
#include <bits/stdc++.h>

using namespace std;

static int total_cats = 0;

class Cat {
public:
    int arrived; // maintain cat's order in the set
    int infection;
    string name;
    Cat(int arrived, int infection, string& name) : arrived{arrived}, infection{infection}, name{name} {};
    bool operator< (const Cat& other) const {
        if (infection == other.infection) return arrived < other.arrived;
        return infection > other.infection;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, command, infection; cin >> n;
    string name; set<Cat> s;
    unordered_map<string, pair<int, int>> m;
    while (n--) {
        cin >> command;
        if (command == 0) {
            cin >> name >> infection;
            Cat cat(total_cats++, infection, name);
            s.emplace(cat);
            m[name] = make_pair(total_cats - 1, infection);
        } else if (command == 1) {
            cin >> name >> infection;
            Cat find_old_cat(m[name].first, m[name].second, name);
            auto it = s.find(find_old_cat);

            Cat old = *it;
            s.erase(it);
            old.infection += infection;
            s.emplace(old);
            m[name].second = old.infection;
        } else if (command == 2) {
            cin >> name;
            Cat cat(m[name].first, m[name].second, name);
            s.erase(s.find(cat));
        }
        else {
            if (s.empty()) cout << "The clinic is empty" << endl;
            else cout << (*s.begin()).name << endl;
        }
    }
}

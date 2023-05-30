#include <bits/stdc++.h>

using namespace std;

class Story {
public:
    int w, h, x, y;
};

vector<Story> stories;

long long backtrack(int idx, vector<int>& stories_so_far) {
    long long ans = 0;
    if (idx == stories.size()) {
        for (int i : stories_so_far) {
            ans += stories[i].w * stories[i].h;
        }
        return ans;
    }
    // don't take this
    ans = max(ans, backtrack(idx + 1, stories_so_far));
    // take this
    bool can = true;
    for (int i : stories_so_far) {
        // overlap condition
        if (stories[i].w + stories[i].x > stories[idx].x && stories[i].x < stories[idx].w + stories[idx].x &&
                stories[i].h + stories[i].y > stories[idx].y && stories[i].y < stories[idx].h + stories[idx].y) {
            can = false; break;
        }
    }
    if (can) {
        stories_so_far.push_back(idx);
        ans = max(ans, backtrack(idx + 1, stories_so_far));
        stories_so_far.pop_back();
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    while (cin >> n && n != 0) {
        stories.clear();
        while (n--) {
            Story story;
            cin >> story.w >> story.h >> story.x >> story.y;
            stories.emplace_back(story);
        }
        vector<int> temp;
        cout << backtrack(0, temp) << '\n';
    }
}
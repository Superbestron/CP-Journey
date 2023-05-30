#include <bits/stdc++.h>

using namespace std;

const double EPS = 1e-9;
string str;

class Node {
public:
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int value) : value{value} {}
};

void insert(Node*& root, int value) {
    if (root == nullptr) {
        root = new Node(value);
        return;
    }
    if (value < root->value) {
        insert(root->left, value);
    } else {
        insert(root->right, value);
    }
}

void traverse(Node*& root, int depth) {
    if (root == nullptr) {
        str += char(depth);
        return;
    }
    traverse(root->left, depth + 1);
    traverse(root->right, depth + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k, val;
    cin >> n >> k;
    Node* root;
    unordered_set<string> s;
    while (n--) {
        str.clear();
        root = nullptr;
        for (int i = 0; i < k; i++) {
            cin >> val;
            insert(root, val);
        }
        traverse(root, 0);
        s.insert(str);
    }
    cout << s.size();
}
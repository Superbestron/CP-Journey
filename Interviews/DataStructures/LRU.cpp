#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

class Node {
  public:
    int x, y;
    Node* prev = nullptr;
    Node* next = nullptr;
};

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        std::size_t h1 = std::hash<int>{}(p.first);
        std::size_t h2 = std::hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};

bool operator==(const Node& lhs, const Node& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

class LRU {
  private:
    Node start{}, end{};
    using Key = std::pair<int,int>;
    unordered_map<Key, Node*, PairHash> map;
    std::size_t capacity;

    void insert_at_start(Node* node) {
        Node* next = start.next;
        start.next = node;
        node->prev = &start;
        node->next = next;
        next->prev = node;
    }

    static void remove_from_list(Node* node) {
        Node* p = node->prev;
        Node* n = node->next;
        p->next = n;
        n->prev = p;
    }

    void touch(Node* node) {
        remove_from_list(node);
        insert_at_start(node);
    }
  public:
    explicit LRU(size_t cap) : capacity(cap) {
        start.next = &end;
        end.prev = &start;
    }

    ~LRU() {
        Node* cur = start.next;
        while (cur != &end) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    void push(int x, int y) {
        Key key{x, y};
        auto it = map.find(key);
        if (it != map.end()) {
            Node* node = it->second;
            touch(node);
        } else {
            if (map.size() == capacity) {
                Node* victim = end.prev;
                Key victim_key{victim->x, victim->y};
                remove_from_list(victim);
                map.erase(victim_key);
                delete victim;
            }

            Node* node = new Node{};
            node->x = x;
            node->y = y;

            insert_at_start(node);
            map[key] = node;
        }
    }
};

int main() {
    LRU cache(5);
}

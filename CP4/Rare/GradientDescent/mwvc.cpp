#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <chrono>

using namespace std;

#define MAX_SIZE 19
#define PARTIAL_BRUTE_FORCE_MAX_SIZE 18
#define ALPHA 2
#define BETA 5
#define TIME_MS 1995

vector<int> tabu;
int N, E;
int no_improve = 0;
int tries = 0;
vector<int> timeStamp;

mt19937 random_num_generator(time(nullptr));
std::chrono::time_point start = std::chrono::steady_clock::now();

struct FastArray {
  FastArray(const int N) : weights(N), num_vertices(N) {
    vertices.reset();
  }

  void set_weight(const int vertex_id, const int weight) {
    //assert(vertex_id < num_vertices);
    weights[vertex_id] = weight;
  }

  void set_vertex(const int vertex_id) {
    // assert(vertex_id < num_vertices);
    // assert(!vertices[vertex_id]);
    vertices[vertex_id] = true;
    score += weights[vertex_id];
    timeStamp[vertex_id] = tries;
  }

  void remove_vertex(const int vertex_id) {
    // assert(vertex_id < num_vertices);
    // assert(vertices[vertex_id]);
    vertices[vertex_id] = false;
    score -= weights[vertex_id];
    timeStamp[vertex_id] = tries;
    // assert(score >= 0);
  }

  bool is_vertex_present(const int vertex_id) const {
    // assert(vertex_id < num_vertices);
    return vertices[vertex_id];
  }

  int get_score() const {
    return score;
  }

  int get_weight(const int vertex_id) const {
    // assert(vertex_id < num_vertices);
    return weights[vertex_id];
  }

  void display_cover() const {
    for (int node = 0; node < num_vertices; node++) {
      if (vertices[node]) {
        cout << node << " ";
      }
    }
    cout << '\n';
  }

  bitset<4000> vertices;
  vector<int> weights;
  const int num_vertices;
  int score = 0;
};

struct FastGraph {
  FastGraph(const int N) : adjMat(N, bitset<4000>().reset()),
                           adjList(N),
                           vertex_to_neighbour_weights_sum(N),
                           num_vertices(N) {
  }

  void add_bidirection_edge(const int a, const int b, const int a_weight, const int b_weight) {
    // assert(a < num_vertices && b < num_vertices);
    adjMat[a][b] = true;
    adjMat[b][a] = true;
    adjList[a].push_back(b);
    adjList[b].push_back(a);
    vertex_to_neighbour_weights_sum[a] += b_weight;
    vertex_to_neighbour_weights_sum[b] += a_weight;
  }

  bool is_connected(const int a, const int b) const {
    // assert(a < num_vertices && b < num_vertices);
    return adjMat[a][b];
  }

  vector<bitset<4000>> adjMat;
  vector<vector<int>> adjList;
  vector<int> vertex_to_neighbour_weights_sum;
  const int num_vertices;
};

struct FastMap {
  FastMap(const int N) : num_vertices(N), vertex_to_count(N) {
    vertices_present.reset();
  }

  void set_present(const int vertex_id, const int count) {
    // assert(vertex_id < num_vertices && !vertices_present[vertex_id]);
    vertices_present[vertex_id] = true;
    vertex_to_count[vertex_id] = count;
    size++;
  }

  void set_not_present(const int vertex_id) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id]);
    vertices_present[vertex_id] = false;
    vertex_to_count[vertex_id] = 0;
    size--;
  }

  void increment(const int vertex_id) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id]);
    vertex_to_count[vertex_id]++;
  }

  void decrement(const int vertex_id) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id] && vertex_to_count[vertex_id] > 0);
    vertex_to_count[vertex_id]--;
  }

  void increase(const int vertex_id, const int amount) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id]);
    vertex_to_count[vertex_id] += amount;
  }

  void decrease(const int vertex_id, const int amount) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id] && vertex_to_count[vertex_id] >= amount);
    vertex_to_count[vertex_id] -= amount;
  }

  int get(const int vertex_id) {
    //assert(vertex_id < num_vertices && vertices_present[vertex_id]);
    return vertex_to_count[vertex_id];
  }

  bool is_present(const int vertex_id) {
    return vertices_present[vertex_id];
  }

  vector<pair<int, int>> get_all_present() const {
    vector<pair<int, int>> details;
    for (int node = 0; node < num_vertices; node++) {
      if (vertices_present[node]) {
        details.push_back({node, vertex_to_count[node]});
      }
    }

    return details;
  }

  const int num_vertices;
  bitset<4000> vertices_present;
  vector<int> vertex_to_count;
  int size = 0;
};

struct MWVC {
  MWVC(const FastArray &initial_vertices, const FastGraph &input_graph, int num_edges) : vertices(initial_vertices),
                                                                                         inferred_vertices(
                                                                                             initial_vertices),
                                                                                         graph(input_graph),
                                                                                         total_edges(num_edges),
                                                                                         selected_vertex_to_unselected_count(
                                                                                             FastMap(graph.num_vertices)),
                                                                                         unselected_vertex_to_selected_count(
                                                                                             FastMap(graph.num_vertices)),
                                                                                         selected_vertex_to_unselected_cost(
                                                                                             FastMap(graph.num_vertices)),
                                                                                         unselected_vertex_to_selected_cost(
                                                                                             FastMap(graph.num_vertices)) {
    for (int node = 0; node < vertices.num_vertices; node++) {
      if (vertices.is_vertex_present(node)) {
        selected_vertex_to_unselected_count.set_present(node, 0);
        selected_vertex_to_unselected_cost.set_present(node, 0);
      } else {
        unselected_vertex_to_selected_count.set_present(node, 0);
        unselected_vertex_to_selected_cost.set_present(node, 0);
      }
    }
    // O(V + E)
    for (int node = 0; node < vertices.num_vertices; node++) {
      if (vertices.is_vertex_present(node)) {
        for (const auto &neigh : graph.adjList[node]) {
          if (!vertices.is_vertex_present(neigh)) {
            // selected node has unselected neigh
            selected_vertex_to_unselected_count.increment(node);
            selected_vertex_to_unselected_cost.increase(node, vertices.get_weight(neigh));
          }
        }
      } else {
        for (const auto &neigh : graph.adjList[node]) {
          if (!vertices.is_vertex_present(neigh)) {
            num_edges_uncovered++;
          } else {
            unselected_vertex_to_selected_count.increment(node);
            unselected_vertex_to_selected_cost.increase(node, vertices.get_weight(neigh));
          }
        }
      }
    }
    //assert(num_edges_uncovered % 2 == 0);
    num_edges_uncovered /= 2;
    // assert(unselected_vertex_to_selected_count.size + selected_vertex_to_unselected_count.size == vertices.num_vertices);
    // assert(unselected_vertex_to_selected_cost.size + selected_vertex_to_unselected_cost.size == vertices.num_vertices);
  }

  void add_vertex_to_cover(const int vertex) {
    // O(V)
    // assert(!selected_vertex_to_unselected_count.is_present(vertex));
    // assert(unselected_vertex_to_selected_count.is_present(vertex));
    // assert(!selected_vertex_to_unselected_cost.is_present(vertex));
    // assert(unselected_vertex_to_selected_cost.is_present(vertex));

    // num_edges_uncovered must stay same or decrease
    const int num_edges_change = graph.adjList[vertex].size() - unselected_vertex_to_selected_count.get(vertex);
    unselected_vertex_to_selected_count.set_not_present(vertex);
    unselected_vertex_to_selected_cost.set_not_present(vertex);
    int num_edges_add = 0;
    int weight_change = 0;
    for (const auto &neigh : graph.adjList[vertex]) {
      if (selected_vertex_to_unselected_count.is_present(neigh)) {
        selected_vertex_to_unselected_count.decrement(neigh);
        selected_vertex_to_unselected_cost.decrease(neigh, vertices.get_weight(vertex));
      } else {
        unselected_vertex_to_selected_count.increment(neigh);
        unselected_vertex_to_selected_cost.increase(neigh, vertices.get_weight(vertex));
        num_edges_add++;
        weight_change += vertices.get_weight(neigh);
      }
    }
    //assert(num_edges_add == num_edges_change);
    num_edges_uncovered -= num_edges_change;
    //assert(num_edges_uncovered >= 0);
    selected_vertex_to_unselected_count.set_present(vertex, num_edges_change);
    selected_vertex_to_unselected_cost.set_present(vertex, weight_change);
    vertices.set_vertex(vertex);
    //assert(unselected_vertex_to_selected_count.size + selected_vertex_to_unselected_count.size == vertices.num_vertices);
    //assert(unselected_vertex_to_selected_cost.size + selected_vertex_to_unselected_cost.size == vertices.num_vertices);
  }

  void remove_vertex_from_cover(const int vertex) {
    // O(V)
    // assert(selected_vertex_to_unselected_count.is_present(vertex));
    // assert(!unselected_vertex_to_selected_count.is_present(vertex));
    // assert(selected_vertex_to_unselected_cost.is_present(vertex));
    // assert(!unselected_vertex_to_selected_cost.is_present(vertex));

    // num_edges_uncovered must stay same or increase
    const int num_edges_change = selected_vertex_to_unselected_count.get(vertex);
    selected_vertex_to_unselected_count.set_not_present(vertex);
    selected_vertex_to_unselected_cost.set_not_present(vertex);
    int num_edges_to_remove = 0;
    int weight_change = 0;
    for (const auto &neigh : graph.adjList[vertex]) {
      if (unselected_vertex_to_selected_count.is_present(neigh)) {
        unselected_vertex_to_selected_count.decrement(neigh);
        unselected_vertex_to_selected_cost.decrease(neigh, vertices.get_weight(vertex));
        num_edges_to_remove++;
      } else {
        selected_vertex_to_unselected_count.increment(neigh);
        selected_vertex_to_unselected_cost.increase(neigh, vertices.get_weight(vertex));
        weight_change += vertices.get_weight(neigh);
      }
    }
    // assert(num_edges_change == num_edges_to_remove);
    num_edges_uncovered += num_edges_change;
    // assert(num_edges_uncovered >= 0);
    vertices.remove_vertex(vertex);
    unselected_vertex_to_selected_count.set_present(vertex, graph.adjList[vertex].size() - num_edges_to_remove);
    unselected_vertex_to_selected_cost.set_present(vertex, weight_change);
    // assert(unselected_vertex_to_selected_count.size + selected_vertex_to_unselected_count.size == vertices.num_vertices);
    // assert(unselected_vertex_to_selected_cost.size + selected_vertex_to_unselected_cost.size == vertices.num_vertices);
  }

  int remove_vertex_by_rmv_rule_definite() {
    // O(V)
    bool initialised_score = false;
    double score;
    int remove_vertex = 0;
    for (const auto &detail : selected_vertex_to_unselected_cost.get_all_present()) {
      const int possible_vertex = detail.first;
      const int delta_cost = -1 * detail.second;
      if (inferred_vertices.is_vertex_present(possible_vertex) || tabu[possible_vertex] == 1) {
        continue;
      }

      double current_score = (double) delta_cost / vertices.get_weight(possible_vertex);
      if (!initialised_score || current_score > score
          || (current_score == score && timeStamp[possible_vertex] < timeStamp[remove_vertex])) {
        initialised_score = true;
        score = current_score;
        remove_vertex = possible_vertex;
      }
    }

    // means there is a non-inferred vertex eligible for removal
    if (initialised_score) {
      // cout << "RMV REMOVED: " << remove_vertex << '\n';
      remove_vertex_from_cover(remove_vertex);
    }
    return graph.adjList[remove_vertex].size();
  }

  int remove_vertex_by_rmv_rule(const vector<pair<int, int>> &all_eligible) {
    // O(V)
    if (all_eligible.size() == 0) {
      return 0;
    }
    size_t index_to_remove = random_num_generator() % all_eligible.size();
    int remove_vertex = all_eligible[index_to_remove].first;
    double score = -1 * all_eligible[index_to_remove].second / vertices.get_weight(remove_vertex);

    for (int i = 0; i < 50; i++) {
      size_t posi = random_num_generator() % all_eligible.size();
      const int possible_vertex = all_eligible[posi].first;
      const int delta_cost = -1 * all_eligible[posi].second;
      if (inferred_vertices.is_vertex_present(possible_vertex) || tabu[possible_vertex] == 1) {
        continue;
      }

      double current_score = (double) delta_cost / vertices.get_weight(possible_vertex);
      if (current_score > score || (current_score == score && timeStamp[possible_vertex] < timeStamp[remove_vertex])) {
        score = current_score;
        remove_vertex = possible_vertex;
      }
    }

    // means there is a non-inferred vertex eligible for removal
    // cout << "RMV REMOVED: " << remove_vertex << '\n';
    remove_vertex_from_cover(remove_vertex);
    return graph.adjList[remove_vertex].size();
  }

  int remove_vertex_by_valid_score_rule(const vector<pair<int, int>> &all_eligible) {
    int remove_vertex = 0;
    long long score;
    bool initialised_score = false;
    for (const auto &detail : all_eligible) {
      const int possible_vertex = detail.first;
      long long wu;
      for (const auto &neigh : graph.adjList[possible_vertex]) {
        if (unselected_vertex_to_selected_count.is_present(neigh)) {
          wu += vertices.get_weight(neigh);
        }
      }

      long long current_score = wu - vertices.get_weight(possible_vertex);
      if (!initialised_score || current_score < score || timeStamp[possible_vertex] < timeStamp[remove_vertex]) {
        initialised_score = true;
        score = current_score;
        remove_vertex = possible_vertex;
      }
    }

    if (initialised_score) {
      remove_vertex_from_cover(remove_vertex);
    }
    return graph.adjList[remove_vertex].size();
  }

  vector<pair<int, int>> get_all_eligible_to_remove() const {
    const auto all_selected = selected_vertex_to_unselected_cost.get_all_present();
    std::vector<std::pair<int, int>> all_eligible;
    for (const auto &selected : all_selected) {
      if (inferred_vertices.is_vertex_present(selected.first)) {
        continue;
      }
      all_eligible.push_back(selected);
    }
    return all_eligible;
  }

  vector<pair<int, int>> get_all_eligible_to_add() const {
    return unselected_vertex_to_selected_cost.get_all_present();
  }

  void remove_random_vertex(const vector<pair<int, int>> &all_eligible) {
    if (all_eligible.size() == 0) {
      return;
    }

    size_t index_to_remove = random_num_generator() % all_eligible.size();
    int remove_vertex = all_eligible[index_to_remove].first;
    while (!vertices.is_vertex_present(remove_vertex)) {
      index_to_remove = random_num_generator() % all_eligible.size();
      remove_vertex = all_eligible[index_to_remove].first;
    }
    // cout << "RANDOM REMOVED: " << remove_vertex << '\n';
    remove_vertex_from_cover(remove_vertex);
  }

  void add_vertex_by_add_rule() {
    // must only be called if incomplete vertex cover
    // assert(num_edges_uncovered > 0);
    // O(V)
    bool initialised_score = false;
    double score;
    int add_vertex = 0;
    for (const auto &detail : unselected_vertex_to_selected_cost.get_all_present()) {
      const int possible_vertex = detail.first;
      const int delta_cost = graph.vertex_to_neighbour_weights_sum[possible_vertex] - detail.second;
      if (delta_cost == 0) {
        continue;
      }
      // assert(!inferred_vertices.is_vertex_present(possible_vertex));
      // assert(delta_cost > 0);
      double current_score = (double) delta_cost / vertices.weights[possible_vertex];
      if (!initialised_score || current_score > score
          || (current_score == score && timeStamp[possible_vertex] < timeStamp[add_vertex])) {
        initialised_score = true;
        score = current_score;
        add_vertex = possible_vertex;
      }
    }

    // assert(initialised_score);
    tabu[add_vertex] = 1;
    add_vertex_to_cover(add_vertex);
    // cout << "ADD RULE: " << add_vertex << '\n';
  }

  void add_random_vertex() {
    const auto all_unselected = unselected_vertex_to_selected_cost.get_all_present();
    const size_t index_to_add = random_num_generator() % all_unselected.size();
    int add_vertex = all_unselected[index_to_add].first;
    tabu[add_vertex] = 1;
    add_vertex_to_cover(add_vertex);
    // cout << "RANDOM ADD: " << add_vertex << '\n';
  }

  void remove_redundant_vertices() {
    for (int node = 0; node < vertices.num_vertices; node++) {
      // means it is selected but yet it has no unselected neighbours
      if (!inferred_vertices.is_vertex_present(node) && selected_vertex_to_unselected_count.is_present(node)
          && selected_vertex_to_unselected_count.get(node) == 0) {
        // assert(selected_vertex_to_unselected_cost.get(node) == 0);
        // cout << "REDUNDANT: " << node << '\n';
        remove_vertex_from_cover(node);
      }
    }
  }

  // Assumes selected are eligible meaning no inferred vertices in here
  void swap_selected_and_unselected(const vector<pair<int, int>> &selected,
                                    const vector<pair<int, int>> &unselected,
                                    int tries) {
    if (selected.size() == 0 || unselected.size() == 0) {
      return;
    }
    bool has_min_pair = false;
    int best_cost;
    pair<int, int> deselect_to_select;
    set<int> previous_selected;
    set<int> previous_unselected;
    int limit = 5;
    while (tries) {
      // The check is done because swap_selected_and_unselected may be called multiple
      // times which results in previously selected nodes become unselected and vice versa
      // We use the same selected and unselected array for performance

      int selected_index = random_num_generator() % selected.size();
      int select_tries = 0;
      while (!vertices.is_vertex_present(selected[selected_index].first) ||
          previous_selected.find(selected[selected_index].first) != previous_selected.end()) {
        select_tries++;
        selected_index = random_num_generator() % selected.size();
        if (select_tries == limit) {
          return;
        }
        continue;
      }
      previous_selected.insert(selected_index);

      select_tries = 0;
      int unselected_index = random_num_generator() % unselected.size();
      while (vertices.is_vertex_present(unselected[unselected_index].first) ||
          previous_unselected.find(unselected[unselected_index].first) != previous_unselected.end()) {
        select_tries++;
        unselected_index = random_num_generator() % unselected.size();
        if (select_tries == limit) {
          return;
        }
        continue;
      }
      previous_unselected.insert(unselected_index);

      const int possible_deselect_vertex = selected[selected_index].first;
      const int
          deselect_delta_cost = -1 * vertices.get_weight(possible_deselect_vertex) + selected[selected_index].second;

      const int possible_select_vertex = unselected[unselected_index].first;
      const int select_delta_cost = vertices.get_weight(possible_select_vertex)
          - (graph.vertex_to_neighbour_weights_sum[possible_select_vertex] - unselected[unselected_index].second);

      if (!has_min_pair
          || best_cost > select_delta_cost + deselect_delta_cost) // || random_num_generator() % 100 <= 10)
      {
        has_min_pair = true;
        best_cost = select_delta_cost + deselect_delta_cost;
        deselect_to_select = {possible_deselect_vertex, possible_select_vertex};
      }
      tries--;
    }

    if (has_min_pair) {
      remove_vertex_from_cover(deselect_to_select.first);
      add_vertex_to_cover(deselect_to_select.second);
      tabu[deselect_to_select.second] = 1;
    }
  }

  int get_vertex_cover_score() {
    // assert(num_edges_uncovered == 0);
    return vertices.get_score();
  }

  bool is_covered() const {
    return num_edges_uncovered == 0;
  }

  FastArray vertices;
  const FastArray inferred_vertices;
  const FastGraph graph;
  const int total_edges;
  int num_edges_uncovered = 0;
  FastMap selected_vertex_to_unselected_count;
  FastMap unselected_vertex_to_selected_count;
  FastMap selected_vertex_to_unselected_cost;
  FastMap unselected_vertex_to_selected_cost;
};

// Article: NuMWVC: A Novel Local Search for Minimum Weighted Vertex Cover Problem
void set_initial_vertices(FastArray &vertices, const FastGraph &graph) {
  map<pair<int, int>, set<pair<int, int>>> n1_n2_w_node;
  for (int node = 0; node < (int) graph.adjList.size(); node++) {
    // Rule 1: If (node has 1 neighbour) and (w(node) is >= w(neighbour)) then neighbour is in mwvc
    if (graph.adjList[node].size() == 1) {
      int neighbour = graph.adjList[node][0];
      if (vertices.get_weight(node) >= vertices.get_weight(neighbour)) {
        if (!vertices.is_vertex_present(neighbour)) {
          vertices.set_vertex(neighbour);
        }
      }
    } else if (graph.adjList[node].size() == 2) {
      // Rule 2: If (node has 2 neighbours n1, n2) and (n1 is connected to n2) and (w(node) >= w(n1) + w(n2)) then n1, n2 is in mwvc
      const int n1 = graph.adjList[node][0];
      const int n2 = graph.adjList[node][1];
      n1_n2_w_node[{n1, n2}].insert({vertices.get_weight(node), node});
      if (graph.is_connected(n1, n2)
          && vertices.get_weight(node) >= vertices.get_weight(n1) + vertices.get_weight(n2)) {
        if (!vertices.is_vertex_present(n1)) {
          vertices.set_vertex(n1);
        }
        if (!vertices.is_vertex_present(n2)) {
          vertices.set_vertex(n2);
        }
      }

      // Rule 3: If (node has 2 neighbours n1, n2) and (n1 is connected to node and n2 only) and (w(node) >= w(n1)) then n1 is in mwvc
      if (graph.is_connected(n1, n2) && graph.adjList[n1].size() == 2
          && vertices.get_weight(node) >= vertices.get_weight(n1)) {
        if (!vertices.is_vertex_present(n1)) {
          vertices.set_vertex(n1);
        }
      }
      if (graph.is_connected(n2, n1) && graph.adjList[n2].size() == 2
          && vertices.get_weight(node) >= vertices.get_weight(n2)) {
        if (!vertices.is_vertex_present(n2)) {
          vertices.set_vertex(n2);
        }
      }
    }
  }

  // Rule 4: If (node_1 has 2 neighbours n1, n2) and (n1 is not connected to n2) and (n1 and n2 are connected to node_2) and (node_2 has only 2 neighbours) and (w(node_1) + w(node_2) >= w(n1) + w(n2)) then n1 and n2 in MWVC
  for (const auto &n1_n2 : n1_n2_w_node) {
    const int n1 = n1_n2.first.first;
    const int n2 = n1_n2.first.second;
    const int weight_to_beat = vertices.get_weight(n1) + vertices.get_weight(n2);
    if (n1_n2.second.size() > 1) {

      auto itr = n1_n2.second.rbegin();
      const int largest_weight = itr->first;
      itr++;
      const int second_weight = itr->first;
      if (largest_weight + second_weight >= weight_to_beat) {
        if (!vertices.is_vertex_present(n1)) {
          vertices.set_vertex(n1);
        }
        if (!vertices.is_vertex_present(n2)) {
          vertices.set_vertex(n2);
        }
      }
    }
  }
}

// Get both vertices and the weight cover
pair<vector<int>, int> partial_brute_force_mwvc(const vector<int> &weights,
                                                const vector<vector<int>> &adjList,
                                                const set<int> &initial_vertices,
                                                const int num_edges) {
  map<int, int> mask_id_to_vertex_id;
  int mask_id = 0;
  for (int vertex_id = 0; vertex_id < (int) weights.size(); vertex_id++) {
    if (initial_vertices.find(vertex_id) == initial_vertices.end()) {
      mask_id_to_vertex_id[mask_id] = vertex_id;
      mask_id++;
    }
  }
  assert(mask_id <= PARTIAL_BRUTE_FORCE_MAX_SIZE);

  vector<int> vertices;
  int best_weight = INT_MAX;
  int best_mask = -1;

  int based_edges_used = 0;
  int based_instance_weight = 0;
  set<int> based_used;
  for (const auto &node : initial_vertices) {
    vertices.push_back(node);
    based_instance_weight += weights[node];
    for (const auto &neigh : adjList[node]) {
      if (based_used.find(neigh) == based_used.end()) {
        based_edges_used++;
      }
    }

    based_used.insert(node);
  }

  for (int mask = 0; mask < (1 << mask_id); mask++) {
    int instance_weight = based_instance_weight;
    int edges_used = based_edges_used;
    set<int> vertices_used;
    for (int vIndex = 0; vIndex < mask_id; vIndex++) {
      if ((1 << vIndex) & mask) {
        const int node = mask_id_to_vertex_id.at(vIndex);
        instance_weight += weights[node];
        for (const auto &neigh : adjList[node]) {
          if (vertices_used.find(neigh) == vertices_used.end() && based_used.find(neigh) == based_used.end()) {
            edges_used++;
          }
        }

        vertices_used.insert(node);
      }
    }

    if (edges_used == num_edges) {
      if (best_weight > instance_weight) {
        best_weight = instance_weight;
        best_mask = mask;
      }
    }
  }

  assert(best_mask != -1);
  for (int vIndex = 0; vIndex < mask_id; vIndex++) {
    if ((1 << vIndex) & best_mask) {
      vertices.push_back(mask_id_to_vertex_id.at(vIndex));
    }
  }

  return {vertices, best_weight};
}

set<int> construct_initial_cover(const vector<int> &weights,
                                 const vector<vector<int>> &adjList,
                                 const set<int> &initial_vertices,
                                 const int num_edges) {
  set<int> cover = initial_vertices;
  for (int node = 0; node < (int) weights.size(); node++) {
    if (initial_vertices.find(node) == initial_vertices.end()) {
      bool is_covered = true;
      for (const auto &neigh : adjList[node]) {
        if (cover.find(neigh) == cover.end()) {
          is_covered = false;
        }
      }
      if (!is_covered) {
        cover.insert(node);
      }
    }
  }

  return cover;
}

void numwvc(FastArray &vertices, const FastGraph &graph, const int num_edges) {
  set_initial_vertices(vertices, graph);

  MWVC m = MWVC(vertices, graph, num_edges);

  bool is_covered = false;
  int score;
  bitset<4000> vertex_cover;
  vertex_cover.reset();

  int rmv_num = ALPHA; // random_num_generator() % int(sqrt(N));
  // vector<bitset<4000>> states_explored;
  int last;
  int random_threshold = 0;

  int tabu_livespan = 100;

  while (true) {
    tries++;
    const auto eligible_to_remove = m.get_all_eligible_to_remove();
    const auto eligible_to_add = m.get_all_eligible_to_add();
    if (random_num_generator() % 100 >= random_threshold) {
      if (random_num_generator() % 100 >= random_threshold) {
        int d1;
        int d2;
        d1 = m.remove_vertex_by_rmv_rule_definite();
        const auto e2 = m.get_all_eligible_to_remove();
        if (no_improve < BETA) {
          d2 = m.remove_vertex_by_valid_score_rule(e2);
        } else {
          d2 = m.remove_vertex_by_rmv_rule(e2);
          no_improve = 0;
        }

        if ((double) d1 + d2 < (double) 2 * 2 * E / N) {
          const auto e3 = m.get_all_eligible_to_remove();
          m.remove_vertex_by_rmv_rule(e3);
        }
      } else {
        m.remove_random_vertex(eligible_to_remove);
      }

    } else {
      m.swap_selected_and_unselected(eligible_to_remove, eligible_to_add, rmv_num);
    }

    fill(tabu.begin(), tabu.end(), 0);

    while (!m.is_covered()) {
      if (random_num_generator() % 1000 >= random_threshold) {
        m.add_vertex_by_add_rule();
      } else {
        m.add_random_vertex();
      }
    }

    m.remove_redundant_vertices();

    int iterate_score = m.get_vertex_cover_score();
    if (!is_covered) {
      last = iterate_score;
    }
    if (last <= iterate_score) {
      no_improve++;
    }

    if (!is_covered || iterate_score < score) {
      is_covered = true;
      score = iterate_score;
      vertex_cover = m.vertices.vertices;
      if (random_threshold > 0) {
        random_threshold--;
      }
    } else {
      if (random_threshold + 1 < 100) {
        random_threshold += 1;
      } else {
        random_threshold = 0;
      }
    }

    last = iterate_score;

    if (std::chrono::steady_clock::now() - start > std::chrono::milliseconds(TIME_MS)) {
      break;
    }
  }

  // unordered_map<bitset<4000>, int> stateToCount;
  // for (auto &state : states_explored)
  // {
  //     stateToCount[state]++;
  // }

  // cout << "NUM DISTINCT STATES: " << stateToCount.size() << '\n';

  // cout << "NUM TRIES: " << tries << '\n';
  cout << score << '\n';
  int count = 0;
  for (int node = 0; node < graph.num_vertices; node++) {
    if (vertex_cover[node]) {
      count++;
      cout << node << " ";
    }
  }
  cout << '\n';
  // cout << "NUM CHOSEN: " << count << '\n';
}

void get_optimal_mwvc(const FastArray &vertices, const FastGraph &graph, const int num_edges) {
  int best_weight = INT_MAX;
  int best_mask = -1;
  for (int mask = 0; mask < (1 << vertices.num_vertices); mask++) {
    int instance_weight = 0;
    int edges_used = 0;
    FastArray used(vertices.num_vertices);
    for (int vIndex = 0; vIndex < vertices.num_vertices; vIndex++) {
      if ((1 << vIndex) & mask) {
        instance_weight += vertices.get_weight(vIndex);
        for (const auto &neigh : graph.adjList[vIndex]) {
          if (!used.is_vertex_present(neigh)) {
            edges_used++;
          }
        }

        used.set_vertex(vIndex);
      }
    }
    if (edges_used == num_edges) {
      if (best_weight > instance_weight) {
        best_weight = instance_weight;
        best_mask = mask;
      }
    }
  }
  cout << best_weight << '\n';
  for (int vIndex = 0; vIndex < MAX_SIZE; vIndex++) {
    if ((1 << vIndex) & best_mask) {
      cout << vIndex << ' ';
    }
  }
  cout << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  // Comment out when not testing with the large test case
  // freopen("large_input_for_test.txt", "r", stdin);

  cin >> N >> E;
  FastArray vertices(N);
  FastGraph graph(N);
  for (int i = 0; i < N; i++) {
    int weight;
    cin >> weight;
    vertices.set_weight(i, weight);
  }
  for (int i = 0; i < E; i++) {
    int a, b;
    cin >> a >> b;
    graph.add_bidirection_edge(a, b, vertices.get_weight(a), vertices.get_weight(b));
  }
  timeStamp.assign(N, 0);
  if (N <= MAX_SIZE) {
    get_optimal_mwvc(vertices, graph, E);
  } else {
    tabu.assign(N, 0);
    numwvc(vertices, graph, E);
  }
  // cout << "NS COUNT: " << (std::chrono::steady_clock::now() - start).count() << '\n';
}

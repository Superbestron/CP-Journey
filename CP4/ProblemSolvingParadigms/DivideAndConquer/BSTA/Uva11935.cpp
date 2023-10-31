#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

vector<ii> events;

bool can(double f) {
  int cur_d = 0, cur_n = 0, leak_rate = 0, dt = 0;
  double original_f = f;
  for (auto &event : events) {
    // for all events, consume this amount of fuel (0 amount if delta time is 0)
    dt = (event.first - cur_d);
    f -= dt / 100.0 * cur_n; // consumption
    f -= (dt) * leak_rate; // leak
    if (f < 0) // quick check
      return false;
    // change a parameter, if needed
    if (event.second <= 0) // Fuel consumption n
      cur_n = -event.second;
    else if (event.second == 1) // Leak
      ++leak_rate;
    else if (event.second == 2) // Gas station
      f = original_f;
    else if (event.second == 3) // Mechanic
      leak_rate = 0;
    else if (event.second == 4) // Goal
      break;
    cur_d = event.first; // update time
  }
  return (f >= 0.0); // if still have enough fuel by goal, this simulation is a success, otherwise, it is a failure
}

int main() {
  int n;
  while (scanf("0 Fuel consumption %d\n", &n), n) {
    events.clear();
    events.emplace_back(0, -n); // first event
    while (true) {
      int d;
      char line[100];
      scanf("%d ", &d);
      gets(line);
      if (strncmp(line, "Fuel", 4) == 0) { // the first four characters are "Fuel"
        sscanf(line, "Fuel consumption %d", &n);
        events.emplace_back(d, -n);
      } else if (strcmp(line, "Leak") == 0)
        events.emplace_back(d, 1);
      else if (strcmp(line, "Gas station") == 0)
        events.emplace_back(d, 2);
      else if (strcmp(line, "Mechanic") == 0)
        events.emplace_back(d, 3);
      else if (strcmp(line, "Goal") == 0) {
        events.emplace_back(d, 4);
        break;
      }
    }
    double lo = 0.0, hi = 10000.0;
    for (int i = 0; i < 50; ++i) {               // log_2(10000/1e-9) ~= 43
      double mid = (lo + hi) / 2.0;                // looping 50x is enough
      can(mid) ? hi = mid : lo = mid;
    }
    printf("%.3lf\n", hi);                       // this is the answer
  }
}

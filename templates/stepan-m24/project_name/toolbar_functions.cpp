#include "toolbar_functions.h"

#include <algorithm>

string print_all_scores(vector<int> all_scores) {
  string scores;
  for (int i = 0; i < min(5, (int)all_scores.size()); ++i) {
    if (i) scores.push_back(' ');
    scores += to_string(all_scores[i]);
  }
  return scores;
}

string print_time(pair<int, pair<int, int> > t) {
  return to_string(t.second.first) + "/" + to_string(t.second.second) +
         " (round " + to_string(t.first) + ")";
}

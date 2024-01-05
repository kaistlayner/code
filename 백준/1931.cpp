#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool sort_func(pair<int, int> a, pair<int, int> b) {
  if (a.second != b.second) {
    return a.second < b.second;
  } else {
    return a.first < b.first;
  }
}

int main() {
  int N;

  cin >> N;

  vector<pair<int, int> > schedule;

  for (int i = 0; i < N; ++i) {
    int start, end;
    cin >> start >> end;
    pair<int, int> tmp = make_pair(start, end);
    schedule.push_back(tmp);
  }

  sort(schedule.begin(), schedule.end(), sort_func);

  int cnt = 0, end_time = 0;

  for (int i = 0; i < schedule.size(); ++i) {
    pair<int, int> cur = schedule[i];

    if (cur.first >= end_time) {
      cout << cur.first << " " << cur.second << endl;
      end_time = cur.second;
      cnt++;
    }
  }

  cout << cnt << endl;

  return 0;
}
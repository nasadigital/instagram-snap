#include "util.h"

#include <bits/stdc++.h>

void export_map(std::map<int, int> tree_map, std::string filename) {
  std::ofstream fout(filename);
  for (auto it : tree_map)
    fout << it.first << "," << it.second << "\n";
  fout.close();
}

void export_vector(std::vector<double> ar, std::string filename) {
  std::ofstream fout(filename);
  for (auto it : ar)
    fout << it << "\n";
  fout.close();
}

void export_timeline(std::vector<std::pair<long long, int>>& vec,
                     std::string filename) {
  std::map<long long, int> tree_map;
  for (auto it : vec) {
    tree_map[it.first]++;
  }
  std::ofstream fout(filename);
  for (auto it : tree_map)
    fout << it.first << "," << it.second << "\n";
  fout.close();
}

double get_average(std::vector<int> ar) {
  double sum = 0;
  for (auto it : ar)
    sum += it;
  return sum / ar.size();
}

double get_median(std::vector<int> ar) {
  if (ar.size() == 1)
    return ar[0];
  nth_element(ar.begin(), ar.begin() + ar.size() / 2, ar.end());
  double rez = ar[ar.size() / 2];
  if (!(ar.size() & 1)) {
    nth_element(ar.begin(), ar.begin() + ar.size() / 2 - 1, ar.end());
    rez = (rez + ar[ar.size() / 2 - 1]) / 2;
  }
  return rez;
}

std::vector<std::string> split(std::string &s, char delim) {
  std::vector<std::string> rez;
  std::string tmp;
  for (uint ctr1 = 0; ctr1 < s.length(); ++ctr1) {
    if (s[ctr1] == delim) {
      rez.push_back(tmp);
      tmp.clear();
    }
    else tmp.push_back(s[ctr1]);
  }
  if (tmp != "")
    rez.push_back(tmp);
  return rez;
}

#include "tagcounter.h"

#include "util.h"

#include <bits/stdc++.h>

void TagCounter::process_line(std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  int id = stoi(split_line[1]);
  long long ts = stoll(split_line[2]);
  for (auto tag : split(split_line[3], ',')) {
    tag_timeline[tag].push_back(std::make_pair(ts, id));
  }
}

std::vector<std::pair<long long, int>>
    TagCounter::get_timeline(std::string tag_name) {
  if (!tag_timeline.count(tag_name)) {
    std::cout << "No tag called " << tag_name << " found!\n";
    return {};
  }
  return tag_timeline[tag_name];
}

void TagCounter::export_occurances(std::string filename) { 
  std::ofstream fout(filename);
  for (auto it : tag_timeline)
    fout << it.first << "," << it.second.size() << "\n";
  fout.close();
}

std::vector<std::pair<long long, int>>
    UniqueTagCounter::get_timeline(std::string tag_name) {
  if (!tag_timeline.count(tag_name)) {
    std::cout << "No tag called " << tag_name << " found!\n";
  }
  std::unordered_map<int, int> first_occ;
  std::vector<std::pair<long long, int>> rez;
  for (auto it : tag_timeline[tag_name]) {
    if (first_occ.count(it.second)) {
      rez[first_occ[it.second]].first =
          std::min(rez[first_occ[it.second]].first, it.first);
    } else {
      first_occ[it.second] = rez.size();
      rez.push_back(it);
    }
  }
  return rez;
}

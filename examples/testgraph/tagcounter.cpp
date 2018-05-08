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

void TagCounter::export_more_timelines(std::vector<std::string> tags,
                                       std::string filename) {
  std::map<long long, std::vector<int>> timelines;
  for (size_t ctr1 = 0; ctr1 < tags.size(); ++ctr1) {
    if (!tag_timeline.count(tags[ctr1])) {
      std::cout << "No tag named: " << tags[ctr1] << "\n";
      return;
    }
    for (auto it : tag_timeline[tags[ctr1]]) {
      if (!timelines.count(it.first))
        timelines[it.first].resize(tags.size());
      ++timelines[it.first][ctr1];
    }
  }
  
  std::ofstream fout(filename);
  fout << "Timestamp";
  for (auto s : tags)
    fout << ",#" << s;
  fout << "\n";
  std::vector<int> cumulative(tags.size());
  for (auto it : timelines) {
    fout << it.first;
    for (size_t ctr1 = 0; ctr1 < it.second.size(); ++ctr1)
      cumulative[ctr1] += it.second[ctr1];
    for (auto val : cumulative)
      fout << "," << val;
    fout << "\n";
  }
  fout.close();
}

void UniqueTagCounter::process_line(std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  int id = stoi(split_line[1]);
  long long ts = stoll(split_line[2]);
  for (auto tag : split(split_line[3], ',')) {
    if (first_occ[tag].count(id)) {
       tag_timeline[tag][first_occ[tag][id]].first =
         std::min(tag_timeline[tag][first_occ[tag][id]].first, ts);
    } else {
      first_occ[tag][id] = tag_timeline[tag].size();
      tag_timeline[tag].push_back(std::make_pair(ts, id));
    }
  }
}

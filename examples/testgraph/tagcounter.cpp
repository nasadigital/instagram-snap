#include "tagcounter.h"

#include "util.h"

#include <bits/stdc++.h>

void TagCounter::process_line(std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  int id = stoi(split_line[1]);
  long long ts = stoll(split_line[2]);
  if (!joined_on.count(id))
    joined_on[id] = ts;
  else
    joined_on[id] = std::min(joined_on[id], ts);
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
                                       std::string filename, bool normalize) {
  std::map<long long, std::vector<int>> timelines;
  std::vector<long long> total_users;
  for (auto it : joined_on)
    total_users.push_back(it.second);
  sort(total_users.begin(), total_users.end());
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
  size_t current_users = 0;
  for (auto it : timelines) {
    fout << it.first;
    while (current_users < total_users.size() && it.first >= total_users[current_users])
      ++current_users;
    for (size_t ctr1 = 0; ctr1 < it.second.size(); ++ctr1)
      cumulative[ctr1] += it.second[ctr1];
    for (auto val : cumulative)
      fout << "," << (normalize ? 1.0 * val / current_users : val);
    fout << "\n";
  }
  fout.close();
}

void UniqueTagCounter::process_line(std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  int id = stoi(split_line[1]);
  long long ts = stoll(split_line[2]);
  if (!joined_on.count(id))
    joined_on[id] = ts;
  else
    joined_on[id] = std::min(joined_on[id], ts);
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

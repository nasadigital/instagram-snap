#include "tagcounter.h"

#include "util.h"

#include <bits/stdc++.h>

void TagCounter::process_line(std::vector<std::string> split_line) {
  if (split_line.size() < 6)
    return;
  int id = stoi(split_line[1]);
  long long ts = stoll(split_line[2]);
  for (auto tag : split(split_line[3], ',')) {
    tag_timeline[tag].push_back(std::make_pair(ts, id));
  }
}

std::vector<std::pair<long long, int>>&
    TagCounter::get_timeline(std::string tag_name) {
  if (!tag_timeline.count(tag_name)) {
    std::cout << "No tag called " << tag_name << " found!\n";
  }
  return tag_timeline[tag_name];
}

#include "property.h"

#include "util.h"

#include <bits/stdc++.h>

void PropertyInDegree::process_userline(
    std::vector<std::string> split_line) {
  indegree[std::stoi(split_line[1])]++;
}

void PropertyOutDegree::process_userline(
    std::vector<std::string> split_line) {
  outdegree[std::stoi(split_line[0])]++;
}

void PropertyInLikes::process_userline(
    std::vector<std::string> split_line) {
  likes[std::stoi(split_line[1])] += std::stoi(split_line[2]);
}

void PropertyOutLikes::process_userline(
    std::vector<std::string> split_line) {
  likes[std::stoi(split_line[0])] += std::stoi(split_line[2]);
}

void PropertyInComments::process_userline(
    std::vector<std::string> split_line) {
  comments[std::stoi(split_line[1])] += std::stoi(split_line[3]);
}

void PropertyOutComments::process_userline(
    std::vector<std::string> split_line) {
  comments[std::stoi(split_line[0])] += std::stoi(split_line[3]);
}

void PropertyMedia::process_medialine(
    std::vector<std::string> split_line) {
  media[stoi(split_line[1])]++;
}

void PropertyTags::process_medialine(
    std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  tags[std::stoi(split_line[1])] += split(split_line[3], ',').size();
}

void PropertyUniqTags::process_medialine(
    std::vector<std::string> split_line) {
  if (split_line.size() < 7)
    return;
  std::vector<std::string> current_tags = split(split_line[3], ',');
  for (auto it : current_tags)
    unique_tags[std::stoi(split_line[1])].insert(it);
}

std::vector<int> PropertyUniqTags::get_properties() {
  for (auto it : unique_tags)
    tags[it.first] = it.second.size();
  return tags;
}

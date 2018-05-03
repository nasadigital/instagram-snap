#include "property.h"

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

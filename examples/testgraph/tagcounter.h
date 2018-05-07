#include <bits/stdc++.h>

class TagCounter {
  std::unordered_map<std::string,
                     std::vector<std::pair<long long, int>>> tag_timeline; 
 public:
  void process_line(std::vector<std::string> split_line);
  std::vector<std::pair<long long, int>>& get_timeline(std::string tag_name);
};

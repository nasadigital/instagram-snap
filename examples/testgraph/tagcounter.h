#include <bits/stdc++.h>

class TagCounter {
 protected:
  std::unordered_map<std::string,
                     std::vector<std::pair<long long, int>>> tag_timeline; 
 public:
  void process_line(std::vector<std::string> split_line);
  virtual std::vector<std::pair<long long, int>> get_timeline(
      std::string tag_name);
  void export_occurances(std::string filename);
};

class UniqueTagCounter : public TagCounter {
  std::vector<std::pair<long long, int>> get_timeline(std::string tag_name);
};

#include <bits/stdc++.h>

class TagCounter {
 protected:
  std::unordered_map<std::string,
                     std::vector<std::pair<long long, int>>> tag_timeline; 
  std::unordered_map<int, long long> joined_on;
 public:
  virtual void process_line(std::vector<std::string> split_line);
  std::vector<std::pair<long long, int>> get_timeline(
      std::string tag_name);
  void export_occurances(std::string filename);
  void export_more_timelines(std::vector<std::string> tags,
                             std::string filename, bool normalize);
};

class UniqueTagCounter : public TagCounter {
  std::unordered_map<std::string, std::unordered_map<int, int>> first_occ;

 public:
  void process_line(std::vector<std::string> split_line);
};

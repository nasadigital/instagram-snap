#include "property.h"
#include "stdafx.h"
#include "tagcounter.h"
#include "util.h"

#include <bits/stdc++.h>
#define GRAPH_SIZE 44766

typedef unsigned int uint;

void export_hm(TIntFltH hm, std::string filename) {
  std::ofstream fout(filename);
  for (auto it = hm.BegI(); it < hm.EndI(); it++)
    fout << it.GetKey() << "," << it.GetDat() << "\n";
  fout.close();
}

std::string get_flag_value(
    std::string parametar_name, int argc, char* argv[]) {
  for (int ctr1 = argc - 1; ctr1 >= 0; --ctr1) {
    std::string command(argv[ctr1]);
    std::vector<std::string> split_line = split(command, '=');
    if (split_line[0] == parametar_name) {
      if (split_line.size() == 1)
        return "true";
      return split_line[1];
    }
  }
  return "";
}

int main(int argc, char* argv[]) {
  typedef TNodeEDatNet<TInt, TInt> WeightedGraph;
  TPt<WeightedGraph> instagram_network = WeightedGraph::New();
  PropertyBase* base_prop;
  bool only_seed = get_flag_value("--only_seed", argc, argv) == "true";
  std::string selected_property = get_flag_value("--property", argc, argv);
  std::string inspect_tags = get_flag_value("--tag_list", argc, argv);
  if (selected_property == "indegree") {
    base_prop = new PropertyInDegree(GRAPH_SIZE);
  } else if (selected_property == "outdegree") {
    base_prop = new PropertyOutDegree(GRAPH_SIZE); 
  } else if (selected_property == "inlikes") {
    base_prop = new PropertyInLikes(GRAPH_SIZE); 
  } else if (selected_property == "outlikes") {
    base_prop = new PropertyOutLikes(GRAPH_SIZE); 
  } else if (selected_property == "incomments") {
    base_prop = new PropertyInComments(GRAPH_SIZE); 
  } else if (selected_property == "outcomments") {
    base_prop = new PropertyOutComments(GRAPH_SIZE); 
  } else if (selected_property == "media") {
    base_prop = new PropertyMedia(GRAPH_SIZE); 
  } else if (selected_property == "tags") {
    base_prop = new PropertyTags(GRAPH_SIZE); 
  } else if (selected_property == "unique_tags") {
    base_prop = new PropertyUniqTags(GRAPH_SIZE); 
  } else {
    std::cout << "Incorrect usage: No such property or no property provided.\n";
    return -1;
  }
  TagCounter* tag_structure = nullptr;
  if (inspect_tags != "") {
    tag_structure = new TagCounter();
  }
  std::cout << "Loading Graph...\n";
  std::ifstream fin("users.csv");
  std::string line;
  std::unordered_set<int> seed_user;
  getline(fin, line);
  while (getline(fin, line)) {
    std::vector<std::string> split_line = split(line, ';'); 
    base_prop->process_userline(split_line);
    int source = std::stoi(split_line[0]);  
    int dest = std::stoi(split_line[1]);  
    while (std::max(source, dest) >= instagram_network->GetMxNId())
      instagram_network->AddNode();
    TInt no_like(std::stoi(split_line[2]));
    instagram_network->AddEdge(source, dest, no_like);
  }
  std::ifstream fin2("media.csv");
  getline(fin2, line);
  while(getline(fin2, line)) {
    std::vector<std::string> split_line = split(line, ';');
    seed_user.insert(std::stoi(split_line[1]));
    base_prop->process_medialine(split_line);
    if (tag_structure)
      tag_structure->process_line(split_line);
  }

  std::cout << "Done Loading Graph!\n";
  
  std::cout << "Start Calculating Statistics...\n";

  std::cout << "Done Calculating Statistics!\n";

  std::cout << "Start Checking Friendship Properties...\n";
  int friends_weak = 0, friends_strong = 0, total_with_friends = 0;
  std::vector<int> property_tidy = base_prop->get_properties();
  int c = 0;

  for (auto it = instagram_network->BegNI();
       it < instagram_network->EndNI(); it++) {
    if (only_seed && !seed_user.count(it.GetId()))
      continue;
    std::vector<int> friend_props;
    int my_prop = property_tidy[it.GetId()];
    for (int e = 0; e < it.GetOutDeg(); e++) {
      if (only_seed && !seed_user.count(it.GetId()))
        continue;
      friend_props.push_back(property_tidy[it.GetOutNId(e)]);
    }
    if (friend_props.size()) {
      ++total_with_friends;
      if (my_prop < get_average(friend_props))
        ++friends_weak;
      if (my_prop < get_median(friend_props))
        ++friends_strong;
    }
    if (false && my_prop < get_average(friend_props) &&
        my_prop >= get_median(friend_props)) {
      c++;
      std::cout << it.GetId() << " : " << my_prop << "\n";
      for (auto item : friend_props)
        std::cout << item << " ";
      std::cout << "\nAverage is: " << get_average(friend_props) << "\n"
                << "Median is: " << get_median(friend_props) << "\n";
    }
  }
  std::cout << "Friendship paradox (weak)   : " << friends_weak << " / "
            << total_with_friends << " - "
            << (100.0 * friends_weak) / total_with_friends << "%\n";
  std::cout << "Friendship paradox (strong) : " << friends_strong << " / "
            << total_with_friends << " - "
            << (100.0 * friends_strong) / total_with_friends << "%\n";

  std::cout << "Done Checking Friendship Properties!\n";
  std::string export_data_filename = get_flag_value("--output_file",
                                                    argc, argv);
  if (export_data_filename != "") {
    std::cout << "Starting to Export Data...\n";
    std::map<int, int> hm;
    for (int ctr1 = 0; ctr1 < GRAPH_SIZE; ++ctr1) {
      if (only_seed && !seed_user.count(ctr1))
        continue;
      hm[property_tidy[ctr1]]++;
    }
    export_map(hm, export_data_filename);
    std::cout << "Done Exporting Data!\n";
  }
  if (tag_structure) {
    std::cout << "Starting to Export Tag Timeline...\n";
    for (auto tag_name : split(inspect_tags, ','))
      export_timeline(tag_structure->get_timeline(tag_name),
                      "tagtm_" + tag_name + ".csv");
    std::cout << "Done Exporting Tag Timeline!\n";
  }
  return 0;
}

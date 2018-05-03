#include <bits/stdc++.h>
#include "property.h"
#include "stdafx.h"
#define GRAPH_SIZE 44766

typedef unsigned int uint;

void export_map(std::map<int, int> tree_map, std::string filename) {
  std::ofstream fout(filename);
  for (auto it : tree_map)
    fout << it.first << "," << it.second << "\n";
  fout.close();
}

void export_hm(TIntFltH hm, std::string filename) {
  std::ofstream fout(filename);
  for (auto it = hm.BegI(); it < hm.EndI(); it++)
    fout << it.GetKey() << "," << it.GetDat() << "\n";
  fout.close();
}

void export_vector(std::vector<double> ar, std::string filename) {
  std::ofstream fout(filename);
  for (auto it : ar)
    fout << it << "\n";
  fout.close();
}

double get_average(std::vector<int> ar) {
  double sum = 0;
  for (auto it : ar)
    sum += it;
  return sum / ar.size();
}

double get_median(std::vector<int> ar) {
  if (ar.size() == 1)
    return ar[0];
  nth_element(ar.begin(), ar.begin() + ar.size() / 2, ar.end());
  double rez = ar[ar.size() / 2];
  if (!(ar.size() & 1)) {
    nth_element(ar.begin(), ar.begin() + ar.size() / 2 - 1, ar.end());
    rez = (rez + ar[ar.size() / 2 - 1]) / 2;
  }
  return rez;
}

std::vector<std::string> split(std::string &s, char delim) {
  std::vector<std::string> rez;
  std::string tmp;
  for (uint ctr1 = 0; ctr1 < s.length(); ++ctr1) {
    if (s[ctr1] == delim) {
      rez.push_back(tmp);
      tmp.clear();
    }
    else tmp.push_back(s[ctr1]);
  }
  if (tmp != "")
    rez.push_back(tmp);
  return rez;
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
  PropertyBase* pBase;
  std::string selected_property = get_flag_value("--property", argc, argv);
  if (selected_property == "indegree") {
    pBase = new PropertyInDegree(GRAPH_SIZE);
  } else if (selected_property == "outdegree") {
    pBase = new PropertyOutDegree(GRAPH_SIZE); 
  } else if (selected_property == "inlikes") {
    pBase = new PropertyInLikes(GRAPH_SIZE); 
  } else if (selected_property == "outlikes") {
    pBase = new PropertyOutLikes(GRAPH_SIZE); 
  } else if (selected_property == "incomments") {
    pBase = new PropertyInComments(GRAPH_SIZE); 
  } else if (selected_property == "outcomments") {
    pBase = new PropertyOutComments(GRAPH_SIZE); 
  } else if (selected_property == "media") {
    pBase = new PropertyMedia(GRAPH_SIZE); 
  } else {
    std::cout << "Incorrect usage: No such property or no property provided\n";
    return -1;
  }
  std::cout << "Random address: " << pBase << "\n";
  std::cout << "Loading Graph...\n";
  std::ifstream fin("users.csv");
  std::string line;
  std::set<int> hash_set;
  getline(fin, line);
  while (getline(fin, line)) {
    std::vector<std::string> split_line = split(line, ';'); 
    pBase->process_userline(split_line);
    int source = std::stoi(split_line[0]);  
    int dest = std::stoi(split_line[1]);  
    while (std::max(source, dest) >= instagram_network->GetMxNId())
      instagram_network->AddNode();
    TInt no_like(std::stoi(split_line[2]));
    instagram_network->AddEdge(source, dest, no_like);
  }
  std::vector<int> pictures_posted(GRAPH_SIZE); 
  std::ifstream fin2("media.csv");
  getline(fin2, line);
  while(getline(fin2, line)) {
    std::vector<std::string> split_line = split(line, ';');
    pictures_posted[std::stoi(split_line[1])]++;
    pBase->process_medialine(split_line);
  }

  std::cout << "Done Loading Graph!\n";
  
  std::cout << "Start Calculating Statistics...\n";

  std::cout << "Done Calculating Statistics!\n";

  std::cout << "Start Checking Friendship Properties...\n";
  int friends_weak = 0, friends_strong = 0, total_with_friends = 0;
  std::vector<int> property_tidy = pBase -> get_properties();
  int c = 0;

  for (auto it = instagram_network->BegNI();
       it < instagram_network->EndNI(); it++) {
    std::vector<int> friend_props;
    int my_prop = property_tidy[it.GetId()];
    for (int e = 0; e < it.GetOutDeg(); e++) {
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
      hm[property_tidy[ctr1]]++;
    }
    export_map(hm, export_data_filename);
    std::cout << "Done Exporting Data!\n";
  }
  return 0;
}

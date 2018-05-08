#include <bits/stdc++.h>

void export_map(std::map<int, int> tree_map, std::string filename);

void export_vector(std::vector<double> ar, std::string filename);

void export_timeline(std::vector<std::pair<long long, int>> vec,
                     std::string filename);

double get_average(std::vector<int> ar);

double get_median(std::vector<int> ar);

std::vector<std::string> split(std::string &s, char delim);

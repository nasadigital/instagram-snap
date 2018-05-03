#include <bits/stdc++.h>

class PropertyBase {
 public:
  virtual void process_userline(std::vector<std::string> split_line) = 0;
  virtual void process_medialine(std::vector<std::string> split_line) = 0;
  virtual std::vector<int> get_properties() = 0;
};

class PropertyInDegree : public PropertyBase {
  std::vector<int> indegree;
 public:
  PropertyInDegree(int size) { indegree.clear(); indegree.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return indegree; }
};

class PropertyOutDegree : public PropertyBase {
  std::vector<int> outdegree;
 public:
  PropertyOutDegree(int size) { outdegree.clear(); outdegree.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return outdegree; };
};

class PropertyInLikes : public PropertyBase {
  std::vector<int> likes;
 public:
  PropertyInLikes(int size) { likes.clear(); likes.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return likes; };
};

class PropertyOutLikes : public PropertyBase {
  std::vector<int> likes;
 public:
  PropertyOutLikes(int size) { likes.clear(); likes.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return likes; };
};

class PropertyInComments : public PropertyBase {
  std::vector<int> comments;
 public:
  PropertyInComments(int size) { comments.clear(); comments.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return comments; };
};

class PropertyOutComments : public PropertyBase {
  std::vector<int> comments;
 public:
  PropertyOutComments(int size) { comments.clear(); comments.resize(size); }
  void process_userline(std::vector<std::string> split_line);
  void process_medialine(std::vector<std::string> split_line) {} 
  std::vector<int> get_properties() { return comments; };
};

class PropertyMedia : public PropertyBase {
  std::vector<int> media;
 public:
  PropertyMedia(int size) { media.clear(); media.resize(size); }
  void process_userline(std::vector<std::string> split_line) {}
  void process_medialine(std::vector<std::string> split_line); 
  std::vector<int> get_properties() { return media; };
};

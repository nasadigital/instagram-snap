#include <bits/stdc++.h>
#include "stdafx.h"
#define GRAPH_SIZE 44766

typedef unsigned int uint;


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

int main(int argc, char* argv[]) {
  typedef TNodeEDatNet<TInt, TInt> WeightedGraph;
  TPt<WeightedGraph> instagram_network = WeightedGraph::New();
  
  std::cout << "Loading Graph...\n";
  std::ifstream fin("users.csv");
  std::string line;
  std::set<int> hash_set;
  getline(fin, line);
  while (getline(fin, line)) {
    std::vector<std::string> split_line = split(line, ';'); 
    int source = std::stoi(split_line[0]);  
    int dest = std::stoi(split_line[1]);  
    while (std::max(source, dest) >= instagram_network->GetMxNId())
      instagram_network->AddNode();
    TInt no_like(std::stoi(split_line[2]));
    instagram_network->AddEdge(source, dest, no_like);
  }
  std::cout << "Done Loading Graph!\n";

  //// what type of graph do you want to use?
  typedef PUNGraph PGraph; // undirected graph
  //typedef PNGraph PGraph;  //   directed graph
  //typedef PNEGraph PGraph;  //   directed multigraph
  //typedef TPt<TNodeNet<TInt> > PGraph;
  //typedef TPt<TNodeEdgeNet<TInt, TInt> > PGraph;

  // this code is independent of what particular graph implementation/type we use
  //printf("Creating graph:\n");
  PGraph G = PGraph::TObj::New();
  for (int n = 0; n < 10; n++) {
    G->AddNode(); // if no parameter is given, node ids are 0,1,...,9
  }
  G->AddEdge(0, 1);
  for (int e = 0; e < 10; e++) {
    const int NId1 = G->GetRndNId();
    const int NId2 = G->GetRndNId();
    if (G->AddEdge(NId1, NId2) != -2) {
      //printf("  Edge %d -- %d added\n", NId1,  NId2); }
    } else {
      //printf("  Edge %d -- %d already exists\n", NId1, NId2); }
    }
  }
  IAssert(G->IsOk());
  //G->Dump();
  // delete
  PGraph::TObj::TNodeI NI = G->GetNI(0);
  //printf("Delete edge %d -- %d\n", NI.GetId(), NI.GetOutNId(0));
  G->DelEdge(NI.GetId(), NI.GetOutNId(0));
  const int RndNId = G->GetRndNId();
  //printf("Delete node %d\n", RndNId);
  G->DelNode(RndNId);
  IAssert(G->IsOk());
  // dump the graph
  //printf("Graph (%d, %d)\n", G->GetNodes(), G->GetEdges());
  for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
    //printf("  %d: ", NI.GetId());
    for (int e = 0; e < NI.GetDeg(); e++) {
      //printf(" %d", NI.GetNbrNId(e)); }
    }
    //printf("\n");
  }
  // dump subgraph
  TIntV NIdV;
  for (PGraph::TObj::TNodeI NI = G->BegNI(); NI < G->EndNI(); NI++) {
    if (NIdV.Len() < G->GetNodes()/2) { NIdV.Add(NI.GetId()); }
  }
  PGraph SubG = TSnap::GetSubGraph(G, NIdV);
  //SubG->Dump();
  // get UNGraph
  { PUNGraph UNG = TSnap::ConvertGraph<PUNGraph>(SubG); }
  // IAssert(UNG->IsOk()); }
  // TSnap::ConvertSubGraph<PNGraph>(G, NIdV)->Dump(); }
  // get NGraph
  { PNGraph NG = TSnap::ConvertGraph<PNGraph>(SubG); }
  // IAssert(NG->IsOk()); }
  // TSnap::ConvertSubGraph<PNGraph>(G, NIdV)->Dump(); }
  // get NEGraph
  { PNEGraph NEG = TSnap::ConvertGraph<PNEGraph>(SubG); }
  // NEG->Dump(); }
  // IAssert(NEG->IsOk()); }
  // TSnap::ConvertSubGraph<PNGraph>(G, NIdV)->Dump(); }

  // TSnap::TestAnf<PUNGraph>();
  return 0;
}

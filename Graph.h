//
// Created by gzn24 on 2023/12/18.
//

#ifndef MAP_GRAPH_H
#define MAP_GRAPH_H


#include <list>

class Graph {
private:
  int numVertices;
  std::list<std::pair<int, int>>* adjacencyList;

public:
  Graph(int vertices);
  ~Graph();
  void addEdge(int src, int dest, int weight);
  void removeEdge(int src, int dest);
  void display();
  // 其他方法：深度优先搜索、广度优先搜索等
};


#endif//MAP_GRAPH_H

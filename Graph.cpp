//
// Created by gzn24 on 2023/12/18.
//

#include "Graph.h"

Graph::Graph(int vertices) {
  numVertices = vertices;
  adjacencyList = new std::list<std::pair<int, int>>[numVertices];
}

Graph::~Graph() {
  delete[] adjacencyList;
}

void Graph::addEdge(int src, int dest, int weight) {
  // 无向图添加两个边
  adjacencyList[src].push_back(std::make_pair(dest, weight));
  adjacencyList[dest].push_back(std::make_pair(src, weight));
}

void Graph::removeEdge(int src, int dest) {
  adjacencyList[src].remove_if([dest](std::pair<int, int> element) {
    return element.first == dest;
  });
  // 如果是无向图，需要同时删除 dest 到 src 的边
  // adjacencyList[dest].remove_if([src](std::pair<int, int> element) {
  //     return element.first == src;
  // });
}

void Graph::display() {
  for (int i = 0; i < numVertices; ++i) {
    std::cout << "Vertex " << i << " is connected to: ";
    for (std::pair<int, int> v : adjacencyList[i]) {
      std::cout << v.first << "(" << v.second << ") ";
    }
    std::cout << std::endl;
  }
}
// 其他方法的实现


#include <vector>
#include <list>
#include <unordered_map>
#include <string>
#include <queue>
#include <limits>
#include <iostream>
#include <stack>

struct PathInfo {
  std::vector<std::string> path;
  std::vector<int> distances; // 存储路径上每两个城市间的距离
  int totalDistance;
};

class Graph {
private:
  std::vector<std::string> cities;
  std::unordered_map<std::string, int> cityIndices;
  std::vector<std::list<std::pair<int, int>>> adjacencyList;

public:
  Graph() = default;
  void addCity(const std::string& cityName);
  void removeCity(const std::string& cityName);
  void addRoad(const std::string& cityA, const std::string& cityB, int distance);
  void removeRoad(const std::string& cityA, const std::string& cityB);
  //std::vector<std::string> dijkstraShortestPath(const std::string& startCity, const std::string& endCity);
  //PathInfo dijkstraShortestPath(unsigned long startCity, const std::string& endCity);
  PathInfo dijkstraShortestPath(const std::string &startCity, const std::string &endCity);
};



#include "Graph.h"
#include <algorithm>

void Graph::addCity(const std::string& cityName) {
  cities.emplace_back(cityName);
  int index = cities.size() - 1; // 新城市的索引
  cityIndices[cityName] = index; // 存储城市名称和其索引的映射关系
  adjacencyList.emplace_back();
}

void Graph::removeCity(const std::string& cityName) {
  auto it = cityIndices.find(cityName);
  if (it != cityIndices.end()) {
    int index = it->second; // 要删除的城市在 cities 中的索引
    cities.erase(cities.begin() + index); // 删除城市
    cityIndices.erase(it); // 删除城市名称和索引的映射关系
    adjacencyList.erase(adjacencyList.begin() + index); // 删除邻接表中的相关边
    // 更新其他城市的索引信息
    for (auto& pair : cityIndices) {
      if (pair.second > index) {
        pair.second--; // 减小索引以保持正确性
      }
    }
    // 在邻接表中更新其他城市的边信息
    for (auto& list : adjacencyList) {
      for (auto& edge : list) {
        if (edge.first > index) {
          edge.first--; // 减小索引以保持正确性
        }
      }
    }
  }
}

void Graph::addRoad(const std::string& cityA, const std::string& cityB, int distance) {
  auto itA = cityIndices.find(cityA);
  auto itB = cityIndices.find(cityB);
  if (itA != cityIndices.end() && itB != cityIndices.end()) {
    int indexA = itA->second;
    int indexB = itB->second;
    adjacencyList[indexA].emplace_back(std::make_pair(indexB, distance));
    adjacencyList[indexB].emplace_back(std::make_pair(indexA, distance));
  }
}

void Graph::removeRoad(const std::string& cityA, const std::string& cityB) {
  auto itA = cityIndices.find(cityA);
  auto itB = cityIndices.find(cityB);
  if (itA != cityIndices.end() && itB != cityIndices.end()) {
    int indexA = itA->second;
    int indexB = itB->second;
    adjacencyList[indexA].remove_if([indexB](std::pair<int, int> element) {
      return element.first == indexB;
    });
    adjacencyList[indexB].remove_if([indexA](std::pair<int, int> element) {
      return element.first == indexA;
    });
  }
}
// 其他方法的实现

PathInfo Graph::dijkstraShortestPath(const std::string& startCity, const std::string& endCity) {
  // ...
  int startIndex = cityIndices[startCity];
  int endIndex = cityIndices[endCity];

  std::vector<std::string> shortestPath;
  std::vector<int> distances;
  int totalDistance = 0;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
  pq.push(std::make_pair(0, startIndex));

  std::vector<bool> visited(cities.size(), false);
  std::vector<int> dist(cities.size(), std::numeric_limits<int>::max());
  std::vector<int> prev(cities.size(), -1);

  dist[startIndex] = 0;

  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();

    if (visited[u]) continue;

    visited[u] = true;

    for (auto& edge : adjacencyList[u]) {
      int v = edge.first;
      int weight = edge.second;

      if (!visited[v] && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        prev[v] = u;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  if (prev[endIndex] != -1) {
    int current = endIndex;
    while (current != -1) {
      shortestPath.push_back(cities[current]);
      current = prev[current];
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    for (size_t i = 0; i < shortestPath.size() - 1; ++i) {
      int cityAIndex = cityIndices[shortestPath[i]];
      int cityBIndex = cityIndices[shortestPath[i + 1]];

      int distance = 0;
      for (const auto& edge : adjacencyList[cityAIndex]) {
        if (edge.first == cityBIndex) {
          distance = edge.second;
          totalDistance += distance;
          break;
        }
      }
      distances.push_back(distance);
    }
  }

  return { shortestPath, distances, totalDistance };
}



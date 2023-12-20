#include "Graph.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <set>

void Graph::init() {
  std::ifstream file("E:/C++/map/mapInformation.txt");
  std::string cityA, cityB;
  int distance;
  while (file >> cityA >> cityB >> distance) {
    if (!cityIndices.count(cityA)) addCity(cityA);
    if (!cityIndices.count(cityB)) addCity(cityB);
    addRoad(cityA, cityB, distance);
  }
}

Graph::~Graph() {
  std::ofstream  file("E:/C++/map/mapInformation.txt");

  for (int i = 0; i < cities.size(); i++) {
    for (auto const& edge : adjacencyList[i]) {
       if (edge.first > i) {
         file << indexCity[i] << " " << indexCity[edge.first] << " " << edge.second << std::endl;
       }
    }
  }
  file.close();
}

void Graph::addCity(const std::string& cityName) {
  if (!cityIndices.count(cityName)) {
    cities.emplace_back(cityName);
    int index = cities.size() - 1; // �³��е�����
    cityIndices[cityName] = index; // �洢�������ƺ���������ӳ���ϵ
    indexCity[index] = cityName;
    adjacencyList.emplace_back();
    std::cout << cityName << "��ӳɹ�" << std::endl;
  } else {
    std::cout << "�ó����Ѵ���" << std::endl;
  }
}

void Graph::removeCity(const std::string& cityName) {
  auto it = cityIndices.find(cityName);
  if (it != cityIndices.end()) {
    int index = it->second; // Ҫɾ���ĳ����� cities �е�����
    auto indexCityIt = indexCity.find(index);
    cities.erase(cities.begin() + index); // ɾ������
    cityIndices.erase(it); // ɾ���������ƺ�������ӳ���ϵ
    indexCity.erase(indexCityIt);
    adjacencyList.erase(adjacencyList.begin() + index); // ɾ���ڽӱ��е���ر�
    // �����������е�������Ϣ
    for (auto& pair : cityIndices) {
      if (pair.second > index) {
        pair.second--; // ��С�����Ա�����ȷ��
        indexCity[pair.second] = pair.first;
      }
    }
    // ���ڽӱ��и����������еı���Ϣ
    for (auto& list : adjacencyList) {
      for (auto it = list.begin(); it != list.end(); it++) {
        if (it->first == index) {
          auto ptr = it--;
          list.erase(ptr);
        } else if (it->first > index) {
          it->first--; // ��С�����Ա�����ȷ��
        }
      }
    }
    std::cout << "���� " << cityName << " ���������ĵ�·�ѱ��Ƴ�" << std::endl;
  } else {
    std::cout << "�Ҳ������� " << cityName << std::endl;
  }

}

void Graph::addRoad(const std::string& cityA, const std::string& cityB, int distance) {
  auto itA = cityIndices.find(cityA);
  auto itB = cityIndices.find(cityB);
  if (itA == itB) {
    std::cout << "��ϵͳ���������Ի�" << std::endl;
  } else if (itA != cityIndices.end() && itB != cityIndices.end()) {
    int indexA = itA->second;
    int indexB = itB->second;
    adjacencyList[indexA].emplace_back(std::make_pair(indexB, distance));
    adjacencyList[indexB].emplace_back(std::make_pair(indexA, distance));
  } else {
    std::cout << "���в�����" << std::endl;
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
    std::cout << "���� " << cityA << " ����� " << cityB << " ֮��ĵ�·�ѱ��Ƴ�" << std::endl;
  } else {
    std::cout << "���в�����" << std::endl;
  }
}
// ����������ʵ��

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

void Graph::print() {
  int flag;
  do {
    std::cin >> flag;
    if (flag == 1) {
      printAdjacencyList();
    } else if (flag == 2) {
      printAdjacencyMatrix();
    } else if (flag == 3) {
      break;
    } else {
      std::cout << "�Ƿ�ѡ�������ѡ��" << std::endl;
    }
  } while (flag != 1 && flag != 2);
}

void Graph::printAdjacencyMatrix() {
  const int INF = 1e9;
  system("cls");
  std::cout << "�ڽӾ���" << std::endl;
  std::cout << std::setw(5) << " ";
  for (auto& cityName : cities) {
    std::cout << std::setw(5) << cityName << " ";
  }
  std::cout << std::endl;
  for (int i = 0; i < cities.size(); ++i) {
    std::cout << std::setw(5) << indexCity[i];
    std::vector<int> distance(cities.size(), INF);
    for (auto& edge : adjacencyList[i]) {
      distance[edge.first] = std::min(distance[edge.first], edge.second);
    }
    for (int j = 0; j < cities.size(); j++) {
      std::cout << std::setw(5) << (distance[j] == INF ? 0 : distance[j]) << " ";
    }
    std::cout << std::endl;
  }
  system("pause");
}

void Graph::printAdjacencyList() {
  system("cls");
  std::cout << "�ڽӱ�" << std::endl;
  for (size_t i = 0; i < adjacencyList.size(); ++i) {
    std::cout << indexCity[i] << " -> ";
    std::set<std::string> neighbors;
    for (const auto& neighbor : adjacencyList[i]) {
      neighbors.insert(indexCity[neighbor.first]);
    }
    for (auto& cityName : neighbors) {
      std::cout << cityName << " ";
    }
    std::cout << std::endl;
  }
  system("pause");
}

void Graph::printNeighbours(const std::string& cityName) {
  if (!cityIndices.count(cityName)) {
    std::cout << "���в�����" << std::endl;
  } else {
    for (const auto& neighbour : adjacencyList[cityIndices[cityName]]) {
      std::cout << indexCity[neighbour.first] << " ";
    }
    std::cout << std::endl;
  }
}


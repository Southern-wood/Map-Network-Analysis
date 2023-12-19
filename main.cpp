#include <iostream>
#include "Graph.h"
#include "Login.h"

int main() {
  LoginModule loginModule;

  std::string username, password;

  std::cout << "请输入用户名：";
  std::cin >> username;

  std::cout << "请输入密码：";
  std::cin >> password;

  if (LoginModule::authenticateUser(username, password)) {
    std::cout << "登录成功！欢迎进入地图导航系统。" << std::endl;
    // 在这里调用你的地图导航系统功能
  } else {
    std::cout << "登录失败，请检查用户名和密码。" << std::endl;
    return 0;
  }


  Graph graph;

  // 添加城市节点
  graph.addCity("北京");
  graph.addCity("上海");
  graph.addCity("广州");
  graph.addCity("深圳");
  graph.addCity("成都");

  // 添加城市间的道路及距离
  graph.addRoad("北京", "上海", 1200);
  //graph.addRoad("北京", "广州", 1800);
  graph.addRoad("上海", "深圳", 1500);
  //graph.addRoad("广州", "深圳", 1000);
  graph.addRoad("北京", "成都", 20000);
  graph.addRoad("上海", "成都", 1700);
  //graph.addRoad("广州", "成都", 1600);
  graph.addRoad("深圳", "成都", 1400);

  // 计算最短路径
  //std::vector<std::string> shortestPath = graph.dijkstraShortestPath("北京", "成都");
  PathInfo shortestPathInfo = graph.dijkstraShortestPath("北京", "成都");


  // 输出最短路径
  std::cout << "最短路径为：" << std::endl;
  //std::wcout << L"从" << startCity << L"到" << endCity << L"的最短路径为：" << std::endl;
  for (size_t i = 0; i < shortestPathInfo.path.size(); ++i) {
    std::cout << shortestPathInfo.path[i];
    if (i < shortestPathInfo.distances.size()) {
      std::cout << " (" << shortestPathInfo.distances[i] << " km)";
    }
    if (i != shortestPathInfo.path.size() - 1) std::cout << " -> ";
  }
  std::cout << std::endl;
  std::cout << "总长度为：" << shortestPathInfo.totalDistance << " km" << std::endl;
  std::cout << std::endl;

  return 0;
}

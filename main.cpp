#include <iostream>
#include "Graph.h"
#include "Login.h"
#include "Menu.h"

int main() {
  LoginModule::printLoginScreen();

  std::string username, password;

  std::cout << "请输入用户名：";
  std::cin >> username;

  std::cout << "请输入密码：";
  std::cin >> password;

  if (!LoginModule::authenticateUser(username, password)) {
    std::cout << "登录失败，请检查用户名和密码。" << std::endl;
    return 0;
  }

  std::cout.flush();
  system("cls");

  std::cout << "登录成功！欢迎使用地图导航系统" << std::endl;

  // -------------- 登录模块结束 ---------------

  Graph graph;
  graph.init();

  std::string cityA, cityB;
  int distance;

  int choice;
  do {
    Menu::displayMenu();
    std::cin >> choice;

    switch (choice) {
      case 1:
        Menu::displaySubmenuPrint();
        graph.print();
        break;
      case 2:
        // 添加节点
        // ...
        std::cout << "添加节点功能尚未实现。" << std::endl;
        break;
      case 3:
        // 删除节点
        // ...
        std::cout << "删除节点功能尚未实现。" << std::endl;
        break;
      case 4:
        std::cout << "请输入道路两端的城市和道路的长度：" << std::endl;
        std::cin >> cityA >> cityB >> distance;
        if (distance <= 0) {
          std::cout << "距离非法" << std::endl;
        } else {
          graph.addRoad(cityA, cityB, distance);
        }
        system("pause");
        break;
      case 5:
        // 删除边
        // ...
        std::cout << "删除边功能尚未实现。" << std::endl;
        break;
      case 6:
        // 查找特定节点的邻近节点
        // ...
        std::cout << "查找特定节点的邻近节点功能尚未实现。" << std::endl;
        break;
      case 7:
        // 查找两个节点之间的最短路径
        // ...
        std::cout << "查找两个节点之间的最短路径功能尚未实现。" << std::endl;
        break;
      case 8:
        std::cout << "退出地图导航系统。" << std::endl;
        break;
      default:
        std::cout << "无效的选项，请重新输入（1-8）。" << std::endl;
    }
  } while (choice != 8);




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

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

  std::string cityA, cityB, city;
  int distance;

  int choice;
  do {
    Menu::displayMenu();
    choice = 0;
    while (!(std::cin >> choice)) {   // 如果输入类型不匹配，则执行循环体
      std::cin.clear();               // reset input 设置标志位为有效
      while (std::cin.get() != '\n')  // 删除没有用的输入
        continue;
      std::cout << "非法输入，请输入一个数字：";
    }

    switch (choice) {
      case 1:
        Menu::displaySubmenuPrint();
        graph.print();
        break;
      case 2:
        std::cout << "请输入城市：";
        std::cin >> city;
        graph.addCity(city);
        system("pause");
        break;
      case 3:
        std::cout << "请输入城市：";
        std::cin >> city;
        graph.removeCity(city);
        system("pause");
        break;
      case 4:
        std::cout << "请输入道路两端的城市和道路的长度：";
        while (std::cin >> cityA >> cityB >> distance) {
          if (distance <= 0) {
            std::cout << "距离非法，请重新输入：" << std::endl;
          } else {
            graph.addRoad(cityA, cityB, distance);
            break;
          }
        }
        system("pause");
        break;
      case 5:
        std::cout << "请输入两座城市：";
        std::cin >> cityA >> cityB;
        graph.removeRoad(cityA, cityB);
        system("pause");
        break;
      case 6:
        std::cout << "请输入城市名：";
        std::cin >> city;
        graph.printNeighbours(city);
        system("pause");
        break;
      case 7:
        std::cout << "请输入起始城市和结束城市：";
        std::cin >> cityA >> cityB;
        graph.dijkstraShortestPath(cityA, cityB);
        system("pause");
        break;
      case 8:
        break;
      default:
        std::cout << "无效的选项，请重新输入（1-8）。" << std::endl;
        system("pause");
    }
  } while (choice != 8);
}

#include <iostream>
#include "Graph.h"
#include "Login.h"
#include "Menu.h"

int main() {
  LoginModule::printLoginScreen();

  std::string username, password;

  std::cout << "�������û�����";
  std::cin >> username;

  std::cout << "���������룺";
  std::cin >> password;

  if (!LoginModule::authenticateUser(username, password)) {
    std::cout << "��¼ʧ�ܣ������û��������롣" << std::endl;
    return 0;
  }

  std::cout.flush();
  system("cls");

  std::cout << "��¼�ɹ�����ӭʹ�õ�ͼ����ϵͳ" << std::endl;

  // -------------- ��¼ģ����� ---------------

  Graph graph;
  graph.init();

  std::string cityA, cityB, city;
  int distance;

  int choice;
  do {
    Menu::displayMenu();
    choice = 0;
    while (!(std::cin >> choice)) {   // ����������Ͳ�ƥ�䣬��ִ��ѭ����
      std::cin.clear();               // reset input ���ñ�־λΪ��Ч
      while (std::cin.get() != '\n')  // ɾ��û���õ�����
        continue;
      std::cout << "�Ƿ����룬������һ�����֣�";
    }

    switch (choice) {
      case 1:
        Menu::displaySubmenuPrint();
        graph.print();
        break;
      case 2:
        std::cout << "��������У�";
        std::cin >> city;
        graph.addCity(city);
        system("pause");
        break;
      case 3:
        std::cout << "��������У�";
        std::cin >> city;
        graph.removeCity(city);
        system("pause");
        break;
      case 4:
        std::cout << "�������·���˵ĳ��к͵�·�ĳ��ȣ�";
        while (std::cin >> cityA >> cityB >> distance) {
          if (distance <= 0) {
            std::cout << "����Ƿ������������룺" << std::endl;
          } else {
            graph.addRoad(cityA, cityB, distance);
            break;
          }
        }
        system("pause");
        break;
      case 5:
        std::cout << "�������������У�";
        std::cin >> cityA >> cityB;
        graph.removeRoad(cityA, cityB);
        system("pause");
        break;
      case 6:
        std::cout << "�������������";
        std::cin >> city;
        graph.printNeighbours(city);
        system("pause");
        break;
      case 7:
        std::cout << "��������ʼ���кͽ������У�";
        std::cin >> cityA >> cityB;
        graph.dijkstraShortestPath(cityA, cityB);
        system("pause");
        break;
      case 8:
        break;
      default:
        std::cout << "��Ч��ѡ����������루1-8����" << std::endl;
        system("pause");
    }
  } while (choice != 8);
}

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
        // ��ӽڵ�
        // ...
        std::cout << "��ӽڵ㹦����δʵ�֡�" << std::endl;
        break;
      case 3:
        // ɾ���ڵ�
        // ...
        std::cout << "ɾ���ڵ㹦����δʵ�֡�" << std::endl;
        break;
      case 4:
        std::cout << "�������·���˵ĳ��к͵�·�ĳ��ȣ�" << std::endl;
        std::cin >> cityA >> cityB >> distance;
        if (distance <= 0) {
          std::cout << "����Ƿ�" << std::endl;
        } else {
          graph.addRoad(cityA, cityB, distance);
        }
        system("pause");
        break;
      case 5:
        // ɾ����
        // ...
        std::cout << "ɾ���߹�����δʵ�֡�" << std::endl;
        break;
      case 6:
        // �����ض��ڵ���ڽ��ڵ�
        // ...
        std::cout << "�����ض��ڵ���ڽ��ڵ㹦����δʵ�֡�" << std::endl;
        break;
      case 7:
        // ���������ڵ�֮������·��
        // ...
        std::cout << "���������ڵ�֮������·��������δʵ�֡�" << std::endl;
        break;
      case 8:
        std::cout << "�˳���ͼ����ϵͳ��" << std::endl;
        break;
      default:
        std::cout << "��Ч��ѡ����������루1-8����" << std::endl;
    }
  } while (choice != 8);




  // ��ӳ��нڵ�
  graph.addCity("����");
  graph.addCity("�Ϻ�");
  graph.addCity("����");
  graph.addCity("����");
  graph.addCity("�ɶ�");

  // ��ӳ��м�ĵ�·������
  graph.addRoad("����", "�Ϻ�", 1200);
  //graph.addRoad("����", "����", 1800);
  graph.addRoad("�Ϻ�", "����", 1500);
  //graph.addRoad("����", "����", 1000);
  graph.addRoad("����", "�ɶ�", 20000);
  graph.addRoad("�Ϻ�", "�ɶ�", 1700);
  //graph.addRoad("����", "�ɶ�", 1600);
  graph.addRoad("����", "�ɶ�", 1400);

  // �������·��
  //std::vector<std::string> shortestPath = graph.dijkstraShortestPath("����", "�ɶ�");
  PathInfo shortestPathInfo = graph.dijkstraShortestPath("����", "�ɶ�");


  // ������·��
  std::cout << "���·��Ϊ��" << std::endl;
  //std::wcout << L"��" << startCity << L"��" << endCity << L"�����·��Ϊ��" << std::endl;
  for (size_t i = 0; i < shortestPathInfo.path.size(); ++i) {
    std::cout << shortestPathInfo.path[i];
    if (i < shortestPathInfo.distances.size()) {
      std::cout << " (" << shortestPathInfo.distances[i] << " km)";
    }
    if (i != shortestPathInfo.path.size() - 1) std::cout << " -> ";
  }
  std::cout << std::endl;
  std::cout << "�ܳ���Ϊ��" << shortestPathInfo.totalDistance << " km" << std::endl;
  std::cout << std::endl;

  return 0;
}

#include "Login.h"
#include <fstream>
#include <iostream>

bool LoginModule::authenticateUser(const std::string& username, const std::string& password) {
  std::ifstream file;
  file.open("user.txt", std::ios::in);
  if (file.is_open()) std::cout << "KO\n";

  std::string storedUsername, storedPassword;
  file >> storedUsername >> storedPassword;
  file.close();
  std::cout
  std::cout << "err : " << storedUsername << " " << storedPassword << '\n';

  if (storedUsername == username && storedPassword == password) {
    std::cout << "OK\n";
    return true;
  }
  return false;
}

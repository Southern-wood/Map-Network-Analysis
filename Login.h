#include <string>

class LoginModule {
public:
  static bool authenticateUser(const std::string& username, const std::string& password);
};


#pragma once
#include <vector>
#include <string>
#include "user.h"

class AuthManager {
private:
    std::vector<User> users;
    bool loggedIn;
    User currentUser;

public:
    AuthManager(const std::vector<User>& users);

    bool login(const std::string& username, const std::string& password);
    void logout();

    bool isLoggedIn() const;
    User getCurrentUser() const;
};

#include "authManager.h"

AuthManager::AuthManager(const std::vector<User>& users)
    : users(users), loggedIn(false) {}

bool AuthManager::login(const std::string& username, const std::string& password) {
    for (const auto& u : users) {
        if (u.username == username && u.password == password) {
            currentUser = u;
            loggedIn = true;
            return true;
        }
    }
    return false;
}

void AuthManager::logout() {
    loggedIn = false;
}

bool AuthManager::isLoggedIn() const {
    return loggedIn;
}

User AuthManager::getCurrentUser() const {
    return currentUser;
}

#include "SessionManager.h"
#include <iostream>
#include <ctime>
using namespace std;
void SessionManager::updateLastActivity() {
    lastActivity = time(nullptr);
}

bool SessionManager::login(const string& username, const string& password) {
    auto& instance = getInstance();

    // Здесь должна быть реальная проверка логина/пароля
    // Для демонстрации считаем любой пароль длиной более 3 символов валидным
    if (password.length() > 3) {
        instance.username = username;
        instance.loggedIn = true;
        instance.updateLastActivity();
        instance.sessionData["username"] = username;
        instance.sessionData["login_time"] = to_string(instance.lastActivity);
        return true;
    }
    return false;
}

void SessionManager::logout() {
    auto& instance = getInstance();
    instance.username = "";
    instance.loggedIn = false;
    instance.sessionData.clear();
}

bool SessionManager::isLoggedIn() {
    auto& instance = getInstance();
    if (instance.loggedIn) {
        time_t now = time(nullptr);
        double elapsed = difftime(now, instance.lastActivity);
        if (elapsed < instance.sessionTimeout) {
            return true;
        }
        logout(); // Автоматический выход при истечении таймаута
    }
    return false;
}

string SessionManager::getUsername() {
    auto& instance = getInstance();
    return instance.isLoggedIn() ? instance.username : "";
}

void SessionManager::setSessionTimeout(int seconds) {
    auto& instance = getInstance();
    instance.sessionTimeout = seconds;
}

void SessionManager::refreshSession() {
    auto& instance = getInstance();
    if (instance.isLoggedIn()) {
        instance.updateLastActivity();
    }
}

map<string, string> SessionManager::getSessionData() {
    auto& instance = getInstance();
    if (instance.isLoggedIn()) {
        return instance.sessionData;
    }
    return {};
}
#include "SessionManager.h"
#include <iostream>
#include <chrono>
#include <thread>

void displaySessionStatus() {
    std::cout << "Session status: " << (SessionManager::isLoggedIn() ? "Logged in" : "Logged out") << std::endl;
    if (SessionManager::isLoggedIn()) {
        std::cout << "Username: " << SessionManager::getUsername() << std::endl;
        auto data = SessionManager::getSessionData();
        std::cout << "Session data:" << std::endl;
        for (const auto& pair : data) {
            std::cout << "  " << pair.first << ": " << pair.second << std::endl;
        }
    }
    std::cout << "------------------------" << std::endl;
}

int main() {
    displaySessionStatus();

    // Попытка входа с неправильным паролем
    std::cout << "Trying to login with short password..." << std::endl;
    bool loginResult = SessionManager::login("admin", "123");
    std::cout << "Login result: " << (loginResult ? "Success" : "Failed") << std::endl;
    displaySessionStatus();

    // Успешный вход
    std::cout << "Trying to login with valid password..." << std::endl;
    loginResult = SessionManager::login("admin", "1234");
    std::cout << "Login result: " << (loginResult ? "Success" : "Failed") << std::endl;
    displaySessionStatus();

    // Установка короткого таймаута
    std::cout << "Setting session timeout to 3 seconds..." << std::endl;
    SessionManager::setSessionTimeout(3);
    displaySessionStatus();

    // Обновление сессии
    std::cout << "Refreshing session..." << std::endl;
    SessionManager::refreshSession();
    displaySessionStatus();

    // Ожидание
    std::cout << "Waiting for session timeout (5 seconds)..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    displaySessionStatus();

    // Выход
    std::cout << "Logging out..." << std::endl;
    SessionManager::logout();
    displaySessionStatus();

    return 0;
}
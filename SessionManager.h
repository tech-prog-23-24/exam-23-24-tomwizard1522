#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <string>
#include <map>
#include <ctime>
using namespace std;
class SessionManager {
private:
    static SessionManager& getInstance() {
        static SessionManager instance;
        return instance;
    }

    SessionManager() = default;
    ~SessionManager() = default;
    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    string username;
    bool loggedIn = false;
    int sessionTimeout = 1800; // 30 минут по умолчанию (в секундах)
    time_t lastActivity = 0;
    map<string, string> sessionData;

    void updateLastActivity();

public:
    static bool login(const string& username, const string& password);
    static void logout();
    static bool isLoggedIn();
    static string getUsername();
    static void setSessionTimeout(int seconds);
    static void refreshSession();
    static map<string, string> getSessionData();
};

#endif // SESSIONMANAGER_H
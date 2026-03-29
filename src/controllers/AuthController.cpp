#include "../../include/controllers/AuthController.h"
#include "../../include/utils/Tools.h"
#include "../../include/utils/Animation.h"
#include <iostream>
#include <limits> 
#include <cstdint> // uint8_t


AuthController::AuthController(const std::string& csvPath)
    : _csvPath(csvPath), _currentUser(nullptr) {

    // Load roster in constructor
    Tools::loadCSV(_cache, _csvPath);
}


bool AuthController::login() {
   
    const u_int8_t MAX_ATTEMPTS = 3;

    for(uint8_t attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        Animation::clearScreen();
        
        Animation::writeLine("\t\t ---[ LOGIN ( attempts: " + std::to_string(attempt) + " / " + std::to_string(MAX_ATTEMPTS)  + ")]---\n\n", Animation::BRIGHT_BLUE, 50);

        std::string username, password;
        Animation::writeLine("Username: ", Animation::BRIGHT_WHITE, 50);
        getline(std::cin >> std::ws, username);
        Animation::writeLine("Password: ", Animation::BRIGHT_WHITE, 50);
        std::cout << Animation::getAnsiCode(Animation::BLACK);
        getline(std::cin >> std::ws, password);
        std::cout << Animation::getAnsiCode(Animation::BRIGHT_WHITE);
        for (const Person& p : _cache) {
    
        }
        //find potential user
        for (const Person& p : _cache) {
            if (p.Surname() == username &&
                p.Password() == Tools::encrypt(password)) {

                // make shared copy of found user
                _currentUser = std::make_shared<Person>(p);

                // loguj uspjesan login
                Tools::writeTXT(
                    Tools::loggerFormat(Tools::dateTimeGenerator(),
                                        username, p.Role(), "LOGIN", "success"),
                                            "../data/log.txt");
                Animation::loading(" Authenticating", 2, 200, Animation::GREEN);
                return true;
        
           }
        }
           Tools::writeTXT(
           Tools::loggerFormat(Tools::dateTimeGenerator(),
                                username, "UNKNOWN", "LOGIN", "failed attempt " + std::to_string(attempt)),
                                                    "../data/log.txt");
            Animation::blinking(" Invalid credentials!", Animation::RED, 200, 2);      
    }

    Animation::clearScreen();

    std::cout << "\n Too many failed attempts. Returning to menu...\n";
    Animation::wait(2);
    return false;
}

void AuthController::logout() {
    if (!_currentUser) return;

     Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _currentUser->Surname(), _currentUser->Role(), "LOGOUT"),
        "../data/log.txt"
    );

    _currentUser = nullptr; // shared_ptr clears itself
}

bool AuthController::registerUser() {
    // only admin can register new user (closed sys)
    if(!isAdmin()) return false;

    Animation::clearScreen();
    Animation::writeLine("\t\t ---[ REGISTER NEW USER ]---\n\n" , Animation::BRIGHT_BLUE, 50);

    std::string username, password, roleStr;
    Animation::writeLine("Username: ", Animation::BRIGHT_WHITE, 50);
    getline(std::cin >> std::ws, username);
        for (const Person& p : _cache)
        if (p.Surname() == username) {
            Animation::clearScreen();
            Animation::writeLine("\n Username already exists!\n", Animation::BRIGHT_RED, 50);
            Animation::wait(2);
            return false;
        }

    Animation::writeLine("Password (min. 8 characters): ", Animation::BRIGHT_WHITE, 50);
    getline(std::cin >> std::ws, password);
        if(password.length() < 8) {
            Animation::clearScreen();
                Animation::writeLine("\n Password must be at least 8 characters long!\n", Animation::BRIGHT_RED, 50);
                Animation::wait(2);
                return false;
         }


    Animation::writeLine("Role (ADMIN/WORKER): ", Animation::BRIGHT_WHITE, 50);
    getline(std::cin >> std::ws, roleStr);
     if(stringToRole(roleStr) == JobRole::UNKNOWN) {
        Animation::clearScreen();
            Animation::writeLine("\n Wrong Role!\n", Animation::BRIGHT_RED, 50);
            Animation::wait(2);
            return false;
     }

     Person newUser(username, Tools::encrypt(password), stringToRole(roleStr));

    _cache.push_back(newUser);
    Tools::appendCSV(newUser, _csvPath);
     
     Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _currentUser->Surname(), _currentUser->Role(),
                            "REGISTER", "created user: " + username),
                                        "../data/log.txt" );
        std::cout << "\n";
        Animation::blinking("                           ---[ PROFILE CREATION SUCCESSFUL ]---", Animation::BRIGHT_YELLOW, 300, 6);
        Animation::wait(2);
        return true;
}

// Getters
std::shared_ptr<Person> AuthController::currentUser() const { return _currentUser; }
bool AuthController::isLoggedIn() const { return _currentUser != nullptr; }
bool AuthController::isAdmin()    const { return isLoggedIn() && _currentUser->RoleEnum() == JobRole::ADMIN; }
bool AuthController::isWorker()   const { return isLoggedIn() && _currentUser->RoleEnum() == JobRole::WORKER; }

const std::vector<Person>& AuthController::cache() const { return _cache; }

void AuthController::updateUser(int idx, const Person& p) {
    if (idx < 0 || idx >= (int)_cache.size()) return;
    _cache[idx] = p;
    Tools::rewriteCSV(_cache, _csvPath);
}
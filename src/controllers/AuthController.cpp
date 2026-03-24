#include "../../include/controllers/AuthController.h"
#include "../../include/utils/Tools.h"
#include "../../include/utils/Animation.h"
#include <iostream>
#include <limits> 
#include <cstdint> // uint8_t
#include <string>


AuthController::AuthController(const std::string& csvPath)
    : _csvPath(csvPath), _currentUser(nullptr) {

    // Load roster in constructor
    Tools::loadCSV(_cache, _csvPath);
}

bool AuthController::login() {
    const u_int8_t MAX_ATTEMPTS = 3;

    for(uint8_t attempt = 1; attempt <= MAX_ATTEMPTS; attempt++) {
        Animation::clearScreen();
        Animation::writeLine("\t\t ---[ LOGIN ( attempts: 1 / " + std::to_string(MAX_ATTEMPTS)  + ")]---\n", Animation::BRIGHT_BLUE, 800);

        std::string username, password;
        Animation::writeLine("Username: ", Animation::BRIGHT_WHITE, 400);
        getline(std::cin, username);
        Animation::writeLine("Password", Animation::BRIGHT_WHITE, 400);
        getline(std::cin, password);

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
                                            "data/log.txt"
                );

             Animation::loading(" Authenticating", 2, 200, Animation::GREEN);
                return true;
        
        }
    }}}

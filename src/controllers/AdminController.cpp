#include "../../include/controllers/AdminController.h"
#include "../../include/views/MenuVIew.h"
#include "../../include/views/TableView.h"
#include "../../include/utils/Tools.h"
#include "../../include/utils/Animation.h"
#include <iostream>

using namespace Animation;
using namespace UI;

AdminController::AdminController(AuthController& auth) 
        : _auth(auth), _firstRender(true) {}

void AdminController::run() {
    while (true) {
        clearScreen();

        // first render — logo + welcome + animated menu
        // subsequent renders — instant menu, no logo
        if (_firstRender) {
            printLogo();
            firstAdminMenu(_auth.currentUser()->Surname());
            _firstRender = false;
            
        } else {
            appearLogo();
            adminMenu();
            
        }
        std::cout << "\n\n\t";
        uint8_t choice = optionBox(FormContext::ADMIN_MENU);

        switch (choice) {
            case 1: readLogsScene();     break;
            case 2: viewBoardScene();    break;
            case 3: viewUsersScene();    break;
            case 4: registerUserScene(); break;
            case 5: changeRoleScene();   break;
            case 0: return; // back to main — logout handled in main.cpp
        }
    }
}

void AdminController::readLogsScene() {
    clearScreen();
    writeLine("\n\t\t ---[ LOG.TXT ]---\n\n", BRIGHT_BLUE, 15);

    bool ok = Tools::loadTXT("../data/log.txt");
    if (!ok) writeLine("\n  log.txt not found or empty.\n", RED, 20);

    // log the read action
    Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _auth.currentUser()->Surname(),
                            _auth.currentUser()->Role(),
                            "READ", "log.txt"),
                              "../data/log.txt"
    );

    std::cout << "\n\n\t";
    optionBox(FormContext::ONLY_BACK);
}

void AdminController::viewBoardScene() {
    clearScreen();
    writeLine("\n\t\t ---[ BOARD.TXT ]---\n\n", BRIGHT_BLUE, 15);

    bool ok = Tools::loadTXT("../data/board.txt");
    if (!ok) writeLine("\n  board.txt not found or empty.\n", RED, 20);

    Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _auth.currentUser()->Surname(),
                            _auth.currentUser()->Role(),
                            "READ", "../board.txt"),
        "../data/log.txt"
    );

    std::cout << "\n\n\t";
    optionBox(FormContext::ONLY_BACK);
}

void AdminController::viewUsersScene() {
    clearScreen();
    // TableView renders the roster directly from auth cache
    usersInfo(_auth.cache());
    std::cout << "\n\n\t";
    optionBox(FormContext::ONLY_BACK);
}

void AdminController::registerUserScene() {
    // registerUser() handles all UI internally (AuthController)
    _auth.registerUser();
    _firstRender = false; // coming back — no logo
}

void AdminController::changeRoleScene() {
    clearScreen();
    writeLine("\n\t\t ---[ CHANGE USER ROLE ]---\n\n", BRIGHT_BLUE, 15);

    // show user list so admin can pick by index
    usersInfo(_auth.cache());

    writeLine("\n  Select user number (0 to cancel): ", BRIGHT_WHITE, 20);
    uint8_t idx = optionBox(FormContext::PICK_USER, _auth.cache().size());
    if (idx == 0) return;

    // idx is 1-based from display, convert to 0-based
    int target = idx - 1;
    const Person& current = _auth.cache()[target];

    writeLine("\n  Current role: ", BRIGHT_WHITE, 20);
    writeLine(current.Role(), BRIGHT_CYAN, 20);
    writeLine("\n  New role (ADMIN/WORKER): ", BRIGHT_WHITE, 20);

    std::string newRole;
    std::cin.ignore();
    getline(std::cin, newRole);

    if (stringToRole(newRole) == JobRole::UNKNOWN) {
        writeLine("\n  Invalid role!\n", RED, 20);
        wait(2);
        return;
    }
// mutate cache copy, update via auth
    Person updated = current;
    updated.setRole(stringToRole(newRole));
    _auth.updateUser(target, updated);

    Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _auth.currentUser()->Surname(),
                            _auth.currentUser()->Role(),
                            "ROLE_CHANGE",
                            current.Surname() + " -> " + newRole),
        "../data/log.txt"
    );

    writeLine("\n  Role updated successfully!\n", BRIGHT_GREEN, 20);
    wait(2);

}
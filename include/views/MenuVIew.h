#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <cstdint>
#include <string>

namespace UI {

    enum FormContext {
    ADMIN_MENU = 1,
    USER_MENU = 2,
    ONLY_BACK= 3,
    PICK_USER = 4
};

// Helpers 
void errorMessage();

// Loadings and logos
void loadingCSV(bool loaded);
inline void printLogo();
inline void appearLogo();

// Menus
void userMenu();
void adminMenu();
void firstUserMenu(const std::string& name);
void firstAdminMenu(const std::string& name);

//Main input handler
uint8_t optionBox(FormContext m);

}

#endif
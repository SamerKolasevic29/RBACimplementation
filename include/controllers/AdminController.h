#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "AuthController.h"

class AdminController {
private:
    AuthController& _auth;
    bool _firstRender;

public:
    AdminController(AuthController& auth);
    void run();

private:
    void readLogsScene();
    void viewBoardScene();
    void viewUsersScene();
    void registerUserScene();
    void changeRoleScene();
};

#endif
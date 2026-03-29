#ifndef WORKERCONTROLLER_H
#define WORKERCONTROLLER_H

#include "AuthController.h"

class WorkerController {
private:
    AuthController& _auth;
    bool _firstRender;

public:
    WorkerController(AuthController& auth);
    void run();

private:
    void viewBoardScene();
    void editBoardScene();
};

#endif
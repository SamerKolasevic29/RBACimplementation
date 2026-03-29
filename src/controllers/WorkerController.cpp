#include "../../include/controllers/WorkerController.h"
#include "../../include/views/MenuVIew.h"
#include "../../include/utils/Tools.h"
#include "../../include/utils/Animation.h"
#include "../../include/editor/Editor.h"
#include <iostream>

using namespace Animation;
using namespace UI;

WorkerController::WorkerController(AuthController& auth)
    : _auth(auth), _firstRender(true) {}

void WorkerController::run() {
    while (true) {
        clearScreen();

        if (_firstRender) {
            printLogo();
            firstWorkerMenu(_auth.currentUser()->Surname());
            _firstRender = false;
        } else {
            appearLogo();
            workerMenu();
        }
        std::cout << "\n\n\t";
        uint8_t choice = optionBox(FormContext::WORKER_MENU);

        switch (choice) {
            case 1: viewBoardScene(); break;
            case 2: editBoardScene(); break;
            case 0: return;
        }
    }
}

void WorkerController::viewBoardScene() {
    clearScreen();
    writeLine("\n\t\t ---[ BOARD.TXT ]---\n\n", BRIGHT_BLUE, 15);

    bool ok = Tools::loadTXT("../data/board.txt");
    if (!ok) writeLine("\n  board.txt not found or empty.\n", RED, 20);

    Tools::writeTXT(
        Tools::loggerFormat(Tools::dateTimeGenerator(),
                            _auth.currentUser()->Surname(),
                            _auth.currentUser()->Role(),
                            "READ", "board.txt"),
        "../data/log.txt"
    );

    std::cout << "\n\n\t";
    optionBox(FormContext::ONLY_BACK);
}

void WorkerController::editBoardScene() {
    // Editor takes over the terminal (ncurses)
    showCursor();
    Editor ed("../data/board.txt",
              _auth.currentUser()->Surname(),
              _auth.currentUser()->Role());

    bool exitedClean = ed.run();

    // log only if file was actually modified
    if (ed.isModified() || exitedClean) {
        Tools::writeTXT(
            Tools::loggerFormat(Tools::dateTimeGenerator(),
                                _auth.currentUser()->Surname(),
                                _auth.currentUser()->Role(),
                                "EDIT", "board.txt"),
            "../data/log.txt"
        );
    }
    // _firstRender stays false — returning to userMenu() instantly
}
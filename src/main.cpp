#include "../include/controllers/AuthController.h"
#include "../include/controllers/AdminController.h"
#include "../include/controllers/WorkerController.h"
#include "../include/views/MenuVIew.h"
#include "../include/utils/Animation.h"

int main() {
    // Single AuthController instance — lives for entire program lifetime
    // Loads CSV once in constructor, holds cache + currentUser
    AuthController auth("../data/users.csv");

    UI::loadingCSV(true); // startup animation

    while (true) {
        // login returns false after 3 failed attempts — loop back to login
        if (!auth.login()) continue;

        // route by role
        if (auth.isAdmin()) {
            AdminController admin(auth);
            admin.run();
        } else if (auth.isWorker()) {
            WorkerController worker(auth);
            worker.run();
        }

        // run() returned — user chose logout (case 0)
        auth.logout();
    }

    return 0;
}
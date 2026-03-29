#include "../../include/views/MenuVIew.h"
#include "../../include/utils/Animation.h"
#include <iostream>

using namespace Animation;

namespace UI {
    
    void errorMessage(){
        clearLines(1);
        blinking("ERROR [Wrong Input!]", RED, 200, 3);
        clearLines(1);
    }

void loadingCSV(bool loaded){
        clearScreen();
        writeLine("Fetching data from server...   ", CYAN, 50);
        bar(8, BRIGHT_CYAN, 100);
        
        if(loaded) {
            clearScreen();
            writeLine("LOAD SUCCESSFUL!", BRIGHT_CYAN, 30);
            wait(1);
            clearScreen();
        }
        else {
            clearScreen();
            writeLine("LOAD UNSUCCESSFUL!", BRIGHT_RED, 30);
            wait(1);
            return;
        }
    }

void printLogo() {
    clearScreen();
    hideCursor();
    // using new writeLineX() for dealing with UTF-8 symbols
    std::string s = R"(██████╗ ██████╗  █████╗  ██████╗              ███████╗██╗   ██╗███████╗)";
    writeLineX("\n\t  " + s + "\n", BRIGHT_CYAN, 17);
    s = R"(██╔══██╗██╔══██╗██╔══██╗██╔════╝              ██╔════╝╚██╗ ██╔╝██╔════╝)";
    writeLineX("\t  " + s +"\n", BRIGHT_CYAN, 17);
    s = R"(██████╔╝██████╔╝███████║██║         █████╗    ███████╗ ╚████╔╝ ███████╗)";
    writeLineX("\t  " + s + "\n", CYAN, 17);
    s = R"(██╔══██╗██╔══██╗██╔══██║██║         ╚════╝    ╚════██║  ╚██╔╝  ╚════██║)";
    writeLineX("\t  " + s + "\n", BRIGHT_BLUE, 17);
    s = R"(██║  ██║██████╔╝██║  ██║╚██████╗              ███████║   ██║   ███████║)";
    writeLineX("\t  " + s + "\n", BLUE, 17);
    s = R"(╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝ ╚═════╝              ╚══════╝   ╚═╝   ╚══════╝)";
    writeLineX("\t  " + s + "\n", MAGENTA, 17);
}

void appearLogo() {
    hideCursor();
    std::cout << getAnsiCode(BRIGHT_CYAN) << "\n\t  "
    << R"(██████╗ ██████╗  █████╗  ██████╗              ███████╗██╗   ██╗███████╗)"
    << "\n\t  " << getAnsiCode(BRIGHT_CYAN)
    << R"(██╔══██╗██╔══██╗██╔══██╗██╔════╝              ██╔════╝╚██╗ ██╔╝██╔════╝)"
    << "\n\t  " << getAnsiCode(CYAN)
    << R"(██████╔╝██████╔╝███████║██║         █████╗    ███████╗ ╚████╔╝ ███████╗)"
    << "\n\t  " << getAnsiCode(BRIGHT_BLUE)
    << R"(██╔══██╗██╔══██╗██╔══██║██║         ╚════╝    ╚════██║  ╚██╔╝  ╚════██║)"
    << "\n\t  " << getAnsiCode(BLUE)
    << R"(██║  ██║██████╔╝██║  ██║╚██████╗              ███████║   ██║   ███████║)"
    << "\n\t  " << getAnsiCode(MAGENTA)
    << R"(╚═╝  ╚═╝╚═════╝ ╚═╝  ╚═╝ ╚═════╝              ╚══════╝   ╚═╝   ╚══════╝)";
}  

void firstWorkerMenu(const std::string& name) {
    writeLine("\n\n\t\t\t\t     WELCOME, ", BRIGHT_WHITE, 20); writeLine(name, BRIGHT_CYAN,20); writeLine("!", BRIGHT_WHITE, 20); 
    writeLine("\n\t\t -------------------------------------------------------\n", MAGENTA, 15);
    writeLine("\n\t\t\t     View content from board.txt", BRIGHT_WHITE, 20); writeLine(" --- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("1", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
    writeLine("\n\t\t\t     Edit content from board.txt", BRIGHT_WHITE, 20); writeLine(" --- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("2", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);  
    writeLine("\n\t\t\t\t         Log out", BRIGHT_WHITE, 20); writeLine("  ---------  ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("0", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
}

void workerMenu() {
    writeLine("\n\t\t -------------------------------------------------------\n", MAGENTA, 1);
    writeLine("\n\t\t\t     View content from board.txt", BRIGHT_WHITE, 5); writeLine(" --- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("1", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
    writeLine("\n\t\t\t     Edit content from board.txt", BRIGHT_WHITE, 5); writeLine(" --- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("2", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);  
    writeLine("\n\t\t\t\t         Log out", BRIGHT_WHITE, 5); writeLine("  ---------  ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("0", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
}

void firstAdminMenu(const std::string& name) {
    writeLine("\n\n\t\t\t\t     WELCOME, ", BRIGHT_WHITE, 20); writeLine(name, BRIGHT_CYAN,20); writeLine("!", BRIGHT_WHITE, 20); 
    writeLine("\n\t\t -------------------------------------------------------\n", MAGENTA, 15);
    writeLine("\n\t\t\t\t Read logs from log.txt", BRIGHT_WHITE, 20); writeLine(" ------- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("1", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
    writeLine("\n\t\t\t       View content from board.txt", BRIGHT_WHITE, 20); writeLine(" ---- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("2", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);  
    writeLine("\n\t\t\t\t   View profiles list", BRIGHT_WHITE, 20); writeLine(" --------- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("3", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
    writeLine("\n\t\t\t\t  Register a new user", BRIGHT_WHITE, 20); writeLine(" --------- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("4", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
    writeLine("\n\t\t\t\t   Change user's role", BRIGHT_WHITE, 20); writeLine(" --------- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("5", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
    writeLine("\n\t\t\t\t\tLog out", BRIGHT_WHITE, 20); writeLine("  -------------- ", WHITE, 20);
    writeLine("[", BLUE, 20); writeLine("0", BRIGHT_CYAN, 20); writeLine("]", BLUE, 20);
}

void adminMenu() {
    writeLine("\n\t\t -------------------------------------------------------\n", MAGENTA, 1);
    writeLine("\n\t\t\t\t Read logs from log.txt", BRIGHT_WHITE, 5); writeLine(" ------- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("1", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
    writeLine("\n\t\t\t       View content from board.txt", BRIGHT_WHITE, 5); writeLine(" ---- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("2", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);  
    writeLine("\n\t\t\t\t   View profiles list", BRIGHT_WHITE, 5); writeLine(" --------- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("3", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
    writeLine("\n\t\t\t\t  Register a new user", BRIGHT_WHITE, 5); writeLine(" --------- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("4", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
    writeLine("\n\t\t\t\t   Change user's role", BRIGHT_WHITE, 5); writeLine(" --------- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("5", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
    writeLine("\n\t\t\t\t\tLog out", BRIGHT_WHITE, 5); writeLine("  -------------- ", WHITE, 5);
    writeLine("[", BLUE, 5); writeLine("0", BRIGHT_CYAN, 5); writeLine("]", BLUE, 5);
}

 uint8_t optionBox(FormContext m, int limit){
        int choice; 
        do {
            writeLine("\033[4mOPTION\033[0m: ", YELLOW, 0);
            std::cin >> choice;
            
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                errorMessage();
                choice = 255;
                continue;
            }
            
            // Validation logic
            int valid = 255;
            switch(m){
                case FormContext::WORKER_MENU:
                    if(choice >= 0 && choice <= 2) valid = choice;
                    break;

                case FormContext::ADMIN_MENU:
                    if(choice >= 0 && choice <= 5) valid = choice;
                    break;
                
                case FormContext::ONLY_BACK:
                    if(choice == 0) valid = choice;
                    break;
                
                case FormContext::PICK_USER:
                    if(choice >= 0 || choice <= limit) valid = choice;
                    break;
            }
            
            if(valid == 255) {
                errorMessage();
                choice = 255;
            }

        } while(choice == 255);
        
        return static_cast<uint8_t>(choice);
    }

}
#include "../../include/views/TableView.h"
#include "../../include/utils/Animation.h"
#include "iomanip"

using namespace Animation;

namespace UI {

    void usersInfo(const std::vector<std::unique_ptr<Person>>& roster){
         writeLine("\n\n\t\t\t\t-/ FIGHTERS INFO \\-\n\n", WHITE, 1);
         writeLine("  |      Username      |",BRIGHT_BLACK, 5); writeLine("    Role    ", BRIGHT_BLACK, 5); 
         std::cout << "|\n=======================================================================================\n"; 

         for(size_t i = 0; i < roster.size(); i++){
              std::cout << std::setw(2) << std::right << i + 1 << ". ";
              writeLine(roster[i]->Surname(), WHITE, 20);
              std::cout <<  std::setw(16 - roster[i]->Surname().length()) << std::setfill(' ') << "|";
              writeLine(roster[i]->Role(), BRIGHT_GREEN, 20);
              std::cout <<  std::setw(15 - roster[i]->Role().length()) << std::setfill(' ') << "|\n\n";
         }
     }

}
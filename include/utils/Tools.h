#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include "../models/Person.h" // for Person definition

namespace Tools {

 // CSV Operations 
    bool loadCSV(std::vector<Person>& people, const std::string& filename);
    bool writeCSV(const Person& p, const std::string& filename, bool append);  // append == true; edit == false;

 // TXT Operations (only read method, edit method is in Editor files)
    bool loadTXT(const std::string& filename);
    bool writeTXT(const std::string& row, const std::string& filename);

 // Logger format
    std::string loggerFormat(const std::string& dateTime, const std::string& username, 
                             const std::string& role, const std::string action, 
                             const std::string& details = "");   

 // encrypt/decrypt just a simple simulation, in real-life situations, SHA256, salting...
    std::string encryptDecrypt(const std::string& toEncrypt);

 // DateTime generator
    std::string dateTimeGenerator();
}

#endif
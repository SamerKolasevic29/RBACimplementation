#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <string>
#include "../models/Person.h" // for Person definition

// Base64 table
static const std::string B64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

namespace Tools {

 // CSV Operations 
    bool loadCSV(std::vector<Person>& people, const std::string& filename);
    bool appendCSV(const Person& p, const std::string& filename);
    bool rewriteCSV(const std::vector<Person>& people, const std::string& filename);
    
 // TXT Operations (only read method, edit method is in Editor files)
    bool loadTXT(const std::string& filename);
    bool writeTXT(const std::string& row, const std::string& filename);

 // Logger format
    std::string loggerFormat(const std::string& dateTime, const std::string& username, 
                             const std::string& role, const std::string& action, 
                             const std::string& details = "");   


 // ---[ ENCRYPION & DECRYPTION ]---

 // 1. Base64 rncoding/decoding for avoiding ',' in CSV files except like separators
   std::string base64Encode(const std::string& in);
   std::string base64Decode(const std::string& in);

 // 2. classic simple XOR encrypt/decrypt
   std::string encrypt(const std::string& plain);
   std::string decrypt(const std::string& encoded);
 

 // DateTime generator
    std::string dateTimeGenerator();
}

#endif
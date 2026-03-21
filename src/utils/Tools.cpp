#include "../../include/utils/Tools.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

namespace Tools {
    bool loadCSV(std::vector<Person>& people, const std::string& filename) {
        std::ifstream file(filename);
        
        if(!file.is_open())
            return false; 

        std::string line;
        bool firstLine = true;

        while(getline(file, line)){
            if(line.empty()) continue;
            if (firstLine) { firstLine = false; continue; }

            std::stringstream ss(line);
            std::string segment;
            std::vector<std::string> parts;

            while(getline(ss, segment, ',')) {
                parts.push_back(segment);
            }

            // expecting 3 columns: Username, Password, Role
            if(parts.size() >= 3) {
                try {
                    std::string username = parts[0];
                    std::string password = parts[1];
                    std::string role = parts[2];

                    Person p(username, password, stringToRole(role));
                    people.push_back(p);
                }
                catch (...) { continue; }
            }
        }
         return true;
    }

    bool appendCSV(const Person& p, const std::string& filename) {
        std::ofstream file(filename, std::ios::app);
        
        if (!file.is_open()) return false;
        file << p.Surname() + "," + p.Password() + "," + p.Role() << "\n";
            return true;
}

    bool rewriteCSV(const std::vector<Person>& people, const std::string& filename) {
        std::ofstream file(filename, std::ios::trunc);
        
        if (!file.is_open()) return false;
        
        file << "Username,Password,Role\n"; // header
        for (const auto& p : people)
            file << p.Surname() + "," + p.Password() + "," + p.Role() << "\n";
        
            return true;
}
    
    bool loadTXT(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return false;
        std::cout << file.rdbuf(); // whole log on screen
            return true;
    }

    bool writeTXT(const std::string& row, const std::string& filename) {
        std::ofstream file(filename, std::ios::app);
        if (!file.is_open()) return false;
        file << row << "\n";
            return true;
    }

    std::string loggerFormat(const std::string& dateTime, const std::string& username,
                         const std::string& role, const std::string& action,
                         const std::string& details) {

    // [2025-03-20 14:32:01] WORKER alice EDIT "details"
    std::string log = "[" + dateTime + "] " + role + " " + username + " " + action;
    if (!details.empty()) log += " \"" + details + "\"";
    return log;
    }

    // ---[ ENCRYPTING/DECRYPTING FUNCS ]---

    std::string base64Encode(const std::string& in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(B64[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(B64[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
    }

    std::string base64Decode(const std::string& in) {
        std::vector<int> T(256, -1);
        for (int i = 0; i < 64; i++) T[B64[i]] = i;
        std::string out;
        int val = 0, valb = -8;
        for (unsigned char c : in) {
            if (T[c] == -1) break;
            val = (val << 6) + T[c];
            valb += 6;
            if (valb >= 0) {
                out.push_back((val >> valb) & 0xFF);
                valb -= 8;
            }
        }
        return out;
    }

    std::string encrypt(const std::string& plain) {
    std::string key = "RBAC2025";
    std::string xored = plain;
    for (int i = 0; i < (int)plain.size(); i++)
        xored[i] = plain[i] ^ key[i % key.size()];
    return base64Encode(xored); // Secure for CSV
}

    std::string decrypt(const std::string& encoded) {
        std::string key = "RBAC2025";
        std::string xored = base64Decode(encoded);
        for (int i = 0; i < (int)xored.size(); i++)
            xored[i] = xored[i] ^ key[i % key.size()];
        return xored;
    }

    std::string dateTimeGenerator() {
    std::time_t now = std::time(nullptr);
    std::tm* t = std::localtime(&now);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}

} // namespace Tools
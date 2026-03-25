#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <map>
#include <cctype>
#include <algorithm>

enum class JobRole { ADMIN, WORKER, UNKNOWN };     // Opened for adding more roles (Modularity)

// Helper func for Tools::loadCSV, better for adding more later
inline JobRole stringToRole(std::string& s) {

    // making it upper case 
    std::transform(s.begin(), s.end(), s.begin(),
    [](unsigned char c){ return std::toupper(c); });

    static const std::map<std::string, JobRole> mapping = {
        {"WORKER", JobRole::WORKER},
        {"ADMIN", JobRole::ADMIN}
    };

    // it will not throw exc because if 's' is not a existing key, 'it' will be mapping.end()
    auto it = mapping.find(s);

    if(it != mapping.end()) {  return it->second; }
       
    return JobRole::UNKNOWN;
}

class Person {
private:
    std::string _surname;
    std::string _password;
    JobRole _role;

public:
    // Constructors
    Person();
    Person(std::string s, std::string p, JobRole r);
    Person(const Person& p);

    // Getters
    std::string Surname() const;
    std::string Password() const;
    JobRole RoleEnum() const;
    std::string Role() const;

    // Setters
    void setSurname(const std::string& s);
    void setPassword(const std::string& p);
    void setRole(JobRole r);
};



#endif
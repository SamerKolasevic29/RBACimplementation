#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <map>

enum class JobRole { ADMIN, WORKER, UNKNOWN };     // Opened for adding more roles (Modularity)

// Helper func for Tools::loadCSV, better for adding more later
inline JobRole stringToRole(const std::string& s) {
    std::map<std::string, JobRole> mapping = {
        {"WORKER", JobRole::WORKER},
        {"ADMIN", JobRole::ADMIN}
    };

    return mapping.at(s);
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
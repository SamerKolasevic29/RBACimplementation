#ifndef PERSON_H
#define PERSON_H

#include <string>

enum JobRole { ADMIN, WORKER };     // Opened for adding more roles (Modularity)

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
    JobRole Role() const;
    std::string Role_toString() const;

    // Setters
    void setSurname(const std::string& s);
    void setPassword(const std::string& p);
    void setRole(JobRole r);
};



#endif
#include "../../include/models/Person.h"

using std::string;

// Default Constructor
Person::Person() 
    : _surname("Username123"), _password("12345"), _role(JobRole::UNKNOWN) {}

// Parameterized Constructor  
Person::Person(string s, string p, JobRole r)
    : _surname(s), _password(p), _role(r) {}

// Copy Constructor
Person::Person(const Person& p)
    : _surname(p._surname), _password(p._password), _role(p._role) {}


// ---[ GETTERS ]---
string Person::Surname() const { return _surname; }
string Person::Password() const { return _password; }
string Person::Role() const { 
    switch(_role) {

        case ADMIN: return "ADMIN";
        case WORKER: return "WORKER";
        default: return "UNKNOWN";
        
    }
 }
JobRole Person::RoleEnum() const { return _role; }

// ---[ SETTERS ]---
void Person::setSurname(const string& s) { _surname = s; }
void Person::setPassword(const string& p) { _password = p; }
void Person::setRole(JobRole r) { _role = r; }
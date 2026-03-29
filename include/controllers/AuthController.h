#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <vector>
#include <memory>
#include "../models/Person.h"

class AuthController {
private:
    std::vector<Person>  _cache;
    std::shared_ptr<Person>  _currentUser;
    std::string  _csvPath;

public:
    AuthController(const std::string& csvPath);

    // Returns true if login is successful
    bool login();
    void logout();
    bool registerUser(); //only admin can call this

    // Getters
    std::shared_ptr<Person> currentUser() const;
    bool isLoggedIn()  const;
    bool isAdmin()     const;
    bool isWorker()    const;

    // Roster oprations (for AdminController)
    const std::vector<Person>& cache() const;
    void updateUser(int idx, const Person& p);

};
#endif
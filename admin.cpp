#include "Admin.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

//constructor

Admin::Admin(int id,
    const string& name,
    const string& email,
    const string& phone,
    const string& adminCode,
    const string& password,
    const string& department,
    bool          isSuperAdmin,
    const string& address)
    : Person(id, name, email, phone, address),
    adminCode(adminCode),
    password(password),
    department(department),
    isSuperAdmin(isSuperAdmin)
{
    if (adminCode.empty())
        throw InvalidInputException("Admin code cannot be empty");
    if (password.empty())
        throw InvalidInputException("Password cannot be empty");
    if (department.empty())
        throw InvalidInputException("Department cannot be empty");
}

//destructor
Admin::~Admin() {}

//Pure virtual function

string Admin::getRole() const {
    if (isSuperAdmin)
        return "Super Admin";
    return "Admin";
}

void Admin::display() const {
    cout << "================================" << endl;
    cout << "  Role : " << getRole() << endl;
    cout << "  ID: " << personId << endl;
    cout << "  Name : " << name << endl;
    cout << "  Email : " << email << endl;
    cout << "  Phone : " << phone << endl;
    cout << "  Department: " << department << endl;
    cout << "  Admin Code: " << adminCode << endl;
    cout << "  Super Admin: " << (isSuperAdmin ? "Yes" : "No") << endl;
    cout << "================================" << endl;
}

string Admin::toCSV() const {
    ostringstream ss;
    ss << "Admin" << ","
        << personId << ","
        << name << ","
        << email << ","
        << phone << ","
        << address << ","
        << adminCode << ","
        << password << ","
        << department << ","
        << isSuperAdmin;
    return ss.str();
}

//Admin specific getters
string Admin::getAdminCode()    const {
    return adminCode;
}
string Admin::getPassword()     const { 
    return password;
}
string Admin::getDepartment()   const { 
    return department;
}
bool   Admin::getIsSuperAdmin() const { 
    return isSuperAdmin;
}

//Setters

void Admin::setAdminCode(const string& code) {
    if (code.empty())
        throw InvalidInputException("Admin code cannot be empty");
    adminCode = code;
}

void Admin::setPassword(const string& p) {
    if (p.empty())
        throw InvalidInputException("Password cannot be empty");
    password = p;
}

void Admin::setDepartment(const string& dept) {
    if (dept.empty())
        throw InvalidInputException("Department cannot be empty");
    department = dept;
}

void Admin::setIsSuperAdmin(bool s) {
    isSuperAdmin = s;
}

//Admin methods
bool Admin::verifyPassword(const string& pwd) const {
    return password == pwd;
}
#include "Customer.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

//Constructor

Customer::Customer(int id,
    const string& name,
    const string& email,
    const string& phone,
    const string& licenseNumber,
    const string& password,
    const string& address)
    : Person(id, name, email, phone, address),
    licenseNumber(licenseNumber),
    password(password),
    loyaltyPoints(0),
    isBanned(false) {

    if (licenseNumber.empty()) {
        throw InvalidInputException("Lisence Number cannot be empty");
    }
    if (password.empty()) {
        throw InvalidInputException("Password cannot be empty");
    }
}

//Detructor

Customer::~Customer() {}

//Pure virtual function

string Customer::getRole() const {
    return "Customer";
}

void Customer::display() const {
    cout << "================================" << endl;
    cout << "  Role : Customer" << endl;
    cout << "  ID: " << personId << endl;
    cout << "  Name : " << name << endl;
    cout << "  Email: " << email << endl;
    cout << "  Phone: " << phone << endl;
    cout << "  Address: " << address << endl;
    cout << "  License: " << licenseNumber << endl;
    cout << "  Points: " << loyaltyPoints << endl;
    cout << "  Bookings : " << bookingIds.size() << endl;
    cout << "  Banned: " << (isBanned ? "Yes" : "No") << endl;
    cout << "================================" << endl;
}

string Customer::toCSV() const {
    ostringstream ss;
    ss << "Customer" << ","
        << personId << ","
        << name << ","
        << email << ","
        << phone << ","
        << address << ","
        << licenseNumber << ","
        << password << ","
        << loyaltyPoints << ","
        << isBanned;
    return ss.str();
}

//Getters
string Customer::getLisenceNumber() const {
    return licenseNumber; 
}
string Customer::getPassword()      const {
    return password;
}
int    Customer::getLoyaltyPoints() const {
    return loyaltyPoints;
}
bool   Customer::getIsBanned()      const {
    return isBanned;
}

const vector<int>& Customer::getBookingIds() const {
    return bookingIds;
}

//Setters
void Customer::setLisenceNumber(const string& l) {
    if (l.empty())
        throw InvalidInputException("License number cannot be empty");
    licenseNumber = l;
}

void Customer::setPassword(const string& p) {
    if (p.empty())
        throw InvalidInputException("Password cannot be empty");
    password = p;
}

void Customer::setIsBanned(bool banned) {
    isBanned = banned;
}

//methods specific

void Customer::addBookingId(int bookingId) {
    bookingIds.push_back(bookingId);
}

void Customer::removeBookingId(int bookingId) {
    vector<int> updated;
    for (int i = 0; i < bookingIds.size(); i++) {
        if (bookingIds[i] != bookingId) {
            updated.push_back(bookingIds[i]);
        }
    }
    bookingIds = updated;
}

void Customer::addLoyaltyPoints(int pts) {
    if (pts < 0)
        throw InvalidInputException("Loyalty points cannot be negative");
    loyaltyPoints += pts;
}

bool Customer::verifyPassword(const string& pwd) const {
    return password == pwd;
}
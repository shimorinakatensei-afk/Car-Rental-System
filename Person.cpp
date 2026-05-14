#include <iostream>
#include <string>
#include "Person.h"
#include "Exceptions.h"
#include <sstream>
#include <iomanip>
using namespace std;


//Constructor
Person::Person(int id, const string& name, const string& email, const string& phone, const string& address) : personId(id), name(name), email(email), phone(phone), address(address) {
	if (name.empty()) {
		throw InvalidInputException("Name can not be empty.");
	}
	if (email.empty()) {
		throw InvalidInputException("Email can not be empty.");
	}

}
//Destructor
Person::~Person() {}

//Getters
int Person::getPersonId() const {
	return personId;
}
string Person::getName() const {
	return name;
}
string Person::getEmail() const {
	return email;
}
string Person::getPhone() const {
	return phone;
}
string Person::getAddress() const {
	return address;
}

//Setters
void Person::setName(const string& n) {
	if (n.empty()) {
		throw InvalidInputException("Name can not be Empty.");
	}
	else {
		name = n;
	}
}
void Person::setEmail(const string& e) {
	if (e.empty()) {
		throw InvalidInputException("Email can not be empty.");
	}
	else {
		email = e;
	}
}
void Person::setPhone(const string& p) {
	phone = p;
}
void Person::setAddress(const string& a) {
	address = a;
}

//operators overloading
bool Person::operator==(const Person& other) const {
	return personId == other.personId;
}
ostream& operator<<(ostream& os, const Person& p) {
	os << fixed << setprecision(2);
	os << "[" << p.getRole() << "] " << "ID: " << p.personId << " | Name : " << p.getName() << " | " << "Email : " << p.getEmail() << " | " << "Phone : " << p.getPhone()
		<< " | " << "Address : " << p.getAddress() << endl;
	return os;
}
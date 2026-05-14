#pragma once
#include <string>
#include <iostream>
using namespace std;

//Abstarct Base Class 

class Person {
protected:
	int personId;
	string name;
	string email;
	string phone;
	string address;
public:
	Person(int id, const string& name, const string& email, const string& phone, const string& address = "");
	virtual ~Person();

	//Pure virtual function
	//Customer and Admin (implementation)
	virtual string getRole() const = 0;
	virtual void display() const = 0;
	virtual string toCSV() const = 0;


	//Getters
	int getPersonId() const;
	string getName() const;
	string getEmail() const;
	string getPhone() const;
	string getAddress() const;

	//setters
	void setName(const string& n);
	void setEmail(const string& e);
	void setPhone(const string& p);
	void setAddress(const string& a);

	//Operator Overloading

	bool operator==(const Person& other) const;		//compare by PersonID
	friend ostream& operator<<(ostream& os, const Person& p);
};



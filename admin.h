#pragma once
#include "Person.h"
using namespace std;

class Admin : public Person {
private:
	string adminCode;
	string password;
	string department;
	bool isSuperAdmin;
public:

	//Constructoe & Distructor 

	Admin(int id, const string& name, const string& email, const string& phone, const string& adminCode, const string& password, const string& department = "Management", bool superAdmin = false, const string& address = "");


	~Admin() override;


	//overrideing pure virtual functions from person

	string getRole() const override;
	void display() const override;
	string toCSV() const override;

	//Admin Specific getters

	string  getAdminCode() const;
	string getPassword() const;
	string getDepartment() const;
	bool getIsSuperAdmin() const;

	//Admin setters

	void setAdminCode(const string& code);
	void setPassword(const string& pass);
	void setDepartment(const string& dep);
	void setIsSuperAdmin(bool s);

	//Admin methods

	bool verifyPassword(const string& pwd) const;
};


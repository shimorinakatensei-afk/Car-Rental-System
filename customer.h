#pragma once
#include "Person.h"
#include <vector>
using namespace std;

//customer is subclass of a person

class Customer : public Person {
private:
	string licenseNumber;
	string password;
	int loyaltyPoints;
	vector<int> bookingIds;	//stores IDs of all booking made
	bool isBanned;
public:
	Customer(int id, const string& name, const string& email, const string& phone, const string& password, const string& lisenceNumber, const string& address = "");
	~Customer() override;

	//overriding pure virtual function
	string getRole() const override;
	void display() const override;
	string toCSV() const override;

	//customer specific getters
	string getLisenceNumber() const;
	string getPassword() const;
	int getLoyaltyPoints() const;
	bool getIsBanned() const;
	const vector<int>& getBookingIds() const;


	//customer specific setters
	void setLisenceNumber(const string& l);
	void setPassword(const string& p);
	void setIsBanned(bool banned);

	//customer specific methods
	void addBookingId(int bookingId);
	void removeBookingId(int bookingId);
	void addLoyaltyPoints(int pts);
	bool verifyPassword(const string& pwd) const;
};

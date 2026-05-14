#pragma once
#include <iostream>
#include <string>
using namespace std;

//Vehicle abstarct base class

class Vehicle {
protected:
	int vehicleId;
	string brand;
	string model;
	int year;
	string color;
	float mileage;
	bool isAvailable;
public:
	//constructor and virual distructor

	Vehicle(int id, const string& brand, const string& model, int year, const string& color, float mileage = 0);
	virtual ~Vehicle();

	//pure virtual functions 
	virtual float getRentalRate() const = 0;
	virtual string getType() const = 0;
	virtual void displayInfo() const = 0;
	virtual string toCSV() const = 0;
	//Getters

	int getVehicleId() const;
	string getBrand() const;
	string getModel() const;
	int getYear() const;
	string getColor() const;
	float getMileage() const;
	bool getIsAvailable() const;
	string getFullName() const;   //retruns full information: Brand Model (year)

	//Setters
	void setAvailability(bool available);
	void setMileage(float km);
	void setColor(const string& c);
	

	//Operators overloading

	bool operator==(const Vehicle& other) const; //compare by vehicleID
	bool operator<(const Vehicle& other) const; //compare by rental rate
	bool operator>(const Vehicle& other) const; //compare by rental rate

	friend ostream& operator<<(ostream& os, const Vehicle& v);


};

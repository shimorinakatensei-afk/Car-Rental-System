#include "SUV.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

SUV::SUV(int id, const string& brand, const string& model, int year, const string& color, int seatingCapacity, bool has4WD, bool hasRoofRack, bool hasTowPackage, float mileage) : Vehicle(id, brand, model, year, color, mileage), seatingCapacity(seatingCapacity), has4WD(has4WD), hasRoofRack(hasRoofRack), hasTowPackage(hasTowPackage) {
	if (seatingCapacity < 5 || seatingCapacity > 9) {
		throw InvalidInputException("Seating Capacity MUST be between 5 and 9");
	}
}

SUV::~SUV() {}

//Pure Virtual Function
//Base rate  $75 per day 
//+$15 if has 4WD
//+$5 if has Roof Rack and +$10 if has Tow Package

float SUV::getRentalRate() const {
	float rate = 75.0f;
	if (has4WD) {
		rate += 15.0f;
	}
	if (hasRoofRack) {
		rate += 5.0f;
	}
	if (hasTowPackage) {
		rate += 10.0f;
	}
	return rate;
}

string SUV::getType() const {
	return "SUV";
}

void SUV::displayInfo() const {
	cout << fixed << setprecision(2);
	cout << "================================" << endl;
	cout << "Type:   SUV" << endl;
	cout << "ID: " << vehicleId << endl;
	cout << "Car: " << getFullName() << endl;
	cout << "Color:	" << color << endl;
	cout << "Seats: " << seatingCapacity << endl;
	cout << "4WD: " << (has4WD ? "Yes" : "No") << endl;
	cout << "Tow Package: " << (hasTowPackage ? "Yes" : "No") << endl;
	cout << "Mile-Age: " << mileage << "km" << endl;
	cout << "Rate: $" << getRentalRate() << "/day" << endl;
	cout << "Status: " << (isAvailable ? "Available" : "Not Available") << endl;
	cout << "================================" << endl;
}
string SUV::toCSV() const {
	ostringstream ss;
	ss << "SUV" << "," << vehicleId << "," << brand << "," << model << "," << year << "," << color << "," << mileage << "," << seatingCapacity << "," << has4WD << "," << hasRoofRack << "," << hasTowPackage << "," 
		<< isAvailable;
	return ss.str();
}

//Getters

int SUV::getSeatingCapacity() const {
	return seatingCapacity;
}
bool SUV::getHas4WD() const {
	return has4WD;
}
bool SUV::getHasRoofRack() const {
	return hasRoofRack;
}
bool SUV::getHasTowPackage() const {
	return hasTowPackage;
}

//Setters
void SUV::setSeatingCapacity(int s) {
	if (s < 5 || s > 9) {
		throw InvalidInputException("Seating Capacity MUSЕ be between 5 and 9");
	}
	else {
		seatingCapacity = s;
	}
}

void SUV::setHas4WD(bool w) {
	has4WD = w;
}
void SUV::setHasRoofRack(bool r) {
	hasRoofRack = r;
}
void SUV::setHasTowPackage(bool t) {
	hasTowPackage = t;
}
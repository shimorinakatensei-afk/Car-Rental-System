#include "Truck.h"
#include <iostream>
#include <sstream>
#include "Exceptions.h"
#include <iomanip>
#include <string>

using namespace std;
Truck::Truck(int id, const string& brand, const string& model, int year, const string& color, float cargoCapacityTons, bool hasTrailerHitch, bool isExtendedCab, float bedLengthFeet, float mileage) : Vehicle(id, brand,
	model, year, color, mileage), cargoCapacityTons(cargoCapacityTons), hasTrailerHitch(hasTrailerHitch), isExtendedCab(isExtendedCab), bedLengthFeet(bedLengthFeet) {
	if (cargoCapacityTons <= 0) {
		throw InvalidInputException("Cargo Capacity must be greater than 0");
	}
	if (bedLengthFeet <= 0) {
		throw InvalidInputException("Bed Length must be greater than 0");
	}
}

//Destructor

Truck::~Truck() {}
//Pure virtual Functions
//Base rate is $95 and (+$20 for each ton) and (+$15 for trailer hitch) and (+$10 for extended cab)

float Truck::getRentalRate() const {
	float rate = 95.0f;
	if (cargoCapacityTons > 1.0f) {
		rate += (cargoCapacityTons - 1.0f) * 20.0f;
	}

	if (hasTrailerHitch) {
		rate += 15;
	}
	if (isExtendedCab) {
		rate += 10;
	}
	return rate;
}

string Truck::getType() const {
	return "Truck";
}

void Truck::displayInfo() const {
	cout << fixed << setprecision(2);
	cout << "================================" << endl;
	cout << "Type:   Truck" << endl;
	cout << "ID: " << vehicleId << endl;
	cout << "Car: " << getFullName() << endl;
	cout << "Color:	" << color << endl;
	cout << "Cargo: " << cargoCapacityTons << endl;
	cout << "Trailer Hitch: " << (hasTrailerHitch ? "Yes" : "No") << endl;
	cout << "Extended Cab " << (isExtendedCab ? "Yes" : "No") << endl;
	cout << "Mile-Age: " << mileage << "km" << endl;
	cout << "Rate: $" << getRentalRate() << "/day" << endl;
	cout << "Status: " << (isAvailable ? "Available" : "Not Available") << endl;
	cout << "================================" << endl;
}

string Truck::toCSV() const {
	ostringstream ss;
	ss << "Truck" << "," << vehicleId << "," << brand << "," << model << "," << year << "," << color << "," << mileage << "," << cargoCapacityTons << "," << hasTrailerHitch << "," << isExtendedCab << "," << bedLengthFeet << ","
		<< isAvailable;
	return ss.str();
}


//Getters
float Truck::getCargoCapacityTons() const {
	return cargoCapacityTons;
}
bool Truck::getHasTrailerHitch() const {
	return hasTrailerHitch;
}
bool Truck::getIsExtendedCab() const {
	return isExtendedCab;
}
float Truck::getBedLengthFeet() const {
	return bedLengthFeet;
}

//Setters

void Truck::setCargoCapacityTons(float c) {
	if (c <= 0) {
		throw InvalidInputException("Cargo Capacity must be greater than 0");
	}
	cargoCapacityTons = c;
}
void Truck::setHasTrailerHitch(bool h) {
	hasTrailerHitch = h;
}
void Truck::setIsExtendedCab(bool e) {
	isExtendedCab = e;
}
void Truck::setBedLengthFeet(float b) {
	if (b <= 0) {
		throw InvalidInputException("Length must be greater than 0");
	}
	bedLengthFeet = b;
}
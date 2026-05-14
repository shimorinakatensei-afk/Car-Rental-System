#include <iostream>
#include <string>
#include "Vehicle.h"	
#include "Exceptions.h"
#include <sstream>
#include <iomanip>

using namespace std;

Vehicle::Vehicle(int id, const string& brand, const string& model, int year, const string& color, float mileage) : vehicleId(id), brand(brand), model(model), year(year), color(color), mileage(mileage), isAvailable(true) {
	if (brand.empty()) {
		throw InvalidInputException("Brand can not be empty");
	}
	if (model.empty()) {
		throw InvalidInputException("Model can not be empty");
	}
	if (year < 1990 || year > 2100) {
		throw InvalidInputException("Error: Year must be between 1990 and 2100");
	}
	if (mileage < 0) {
		throw InvalidInputException("Mile-age can not be negative");
	}
}

//Destructor

Vehicle::~Vehicle() {}

//Getters

int  Vehicle::getVehicleId() const {
	return vehicleId;
}
string Vehicle::getBrand() const {
	return brand;
}
string Vehicle::getModel() const {
	return model;
}
int Vehicle::getYear() const {
	return year;
}
string Vehicle::getColor() const {
	return color;
}

float Vehicle::getMileage() const {
	return mileage;
}
bool Vehicle::getIsAvailable() const {
	return isAvailable;
}
string Vehicle::getFullName() const {
	return brand + " " + model + " (" + to_string(year) + ")";
}

//Setters

void Vehicle::setMileage(float km) {
	if (km < 0) {
		throw InvalidInputException("Mile-age can not be negative");
	}
	else {
		mileage = km;
	}
}
void Vehicle::setAvailability(bool available) {
	isAvailable = available;
}

void Vehicle::setColor(const string& c) {
	if (c.empty()) {
		throw InvalidInputException("Color can not be empty");
	}
	else {
		color = c;
	}
}

//Operator overloading

bool Vehicle::operator==(const Vehicle& other) const {
	return vehicleId == other.vehicleId;
}

bool Vehicle::operator<(const Vehicle& other) const {
	return getRentalRate() < other.getRentalRate();
}

bool Vehicle::operator>(const Vehicle& other) const {
	return getRentalRate() > other.getRentalRate();
}
ostream& operator<<(ostream& os, const Vehicle& v) {
	os << fixed << setprecision(2);
	os << "[" << v.getType() << "]" << " ID:" << v.vehicleId << " |" << v.getFullName() << " | Color: " << v.getColor() << " | Rate: $" << v.getRentalRate() << "/day" << " | " << (v.isAvailable ? "Available" : "Not Available");
	return os;
}
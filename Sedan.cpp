#include "Sedan.h"
#include "Exceptions.h"	
#include "iostream"
#include <sstream>
#include <iomanip>

using namespace std;

//Sedan Constructor
Sedan::Sedan(int id, string const& brand, string const& model, int year, string const& color, int numDoors, bool hasSunroof, bool hasLeatherSeats, float mileage) : Vehicle(id, brand,
	model, year, color, mileage), numDoors(numDoors), hasSunroof(hasSunroof), hasLeatherSeats(hasLeatherSeats) {
	if (numDoors < 2 || numDoors > 5) {
		throw InvalidInputException("Number of Doors must be between 2 and 5");
	}
}

//destructor
Sedan::~Sedan() {}	

//Pure virtual functions

//base rate  $45 per day
//+$5 if has Sun Roof and +$8 if has Leather Seats

float Sedan::getRentalRate() const {
	float rate = 45.0f;
	if (hasSunroof) {
		rate += 5.0f;
	}
	if (hasLeatherSeats) {
		rate += 8.0f;
	}
	return rate;
}

string Sedan::getType() const {
	return "Sedan";
}

void Sedan::displayInfo() const {
	cout << fixed << setprecision(2);
	cout << "================================" << endl;
	cout << "Type:   Sedan" << endl;
	cout << "ID: " << vehicleId << endl;
	cout << "Car: " << getFullName() << endl;
	cout << "Color:	" << color << endl;
	cout << "Doors: " << numDoors << endl;
	cout << "Sun Roof: " << (hasSunroof ? "Yes" : "No") << endl;
	cout << "Leather Seats: " << (hasLeatherSeats ? "Yes" : "No") << endl;
	cout << "Mile-Age: " << mileage << "km" << endl;
	cout << "Rate: $" << getRentalRate() << "/day";
	cout << "Status: " << (isAvailable ? "Available" : "Not Available") << endl;
	cout << "================================" << endl;
}

string Sedan::toCSV() const {
	ostringstream ss;
	ss << "Sedan" << "," << vehicleId << "," << brand << "," << model << "," << year << "," << color << "," << mileage << "," << numDoors << "," << hasSunroof << "," << hasLeatherSeats
		<< isAvailable;
	return ss.str();
}

//Getters

int Sedan::getNumDoors() const {
	return numDoors;
}
bool Sedan::getHasSunroof() const {
	return hasSunroof;
}
bool Sedan::getHasLeatherSeats() const {
	return hasLeatherSeats;
}

//Setters

void Sedan::setNumDoors(int d) {
	if (d < 2 || d > 5) {
		throw InvalidInputException("Number of Doors MUST be between 2 and 5");
	}
	else {
		numDoors = d;
	}
}
void Sedan::setHasSunroof(bool s) {
	hasSunroof = s;
}
void Sedan::setHasLeatherSeats(bool l) {
	hasLeatherSeats = l;
}


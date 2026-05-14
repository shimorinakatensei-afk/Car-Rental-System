#pragma once
#include "Vehicle.h"
using namespace std;

//Sedan subclass of Vehicle 

class Sedan : public Vehicle {
private:
	int numDoors;
	bool hasSunroof;
	bool hasLeatherSeats;
public:
	Sedan(int id, const string& brand, const string& model, int year, const string& color, int numDoors = 4, bool hasSunroof = false, bool hasLeatherSeats = false, float mileage = 0.0f);
	~Sedan() override;

	//Overrideing pure virutal functions
	float getRentalRate() const override;
	string getType() const override;
	void displayInfo() const override;
	string toCSV() const override;

	//Getters
	int getNumDoors() const;
	bool getHasSunroof() const;
	bool getHasLeatherSeats() const;

	//Setters
	void setNumDoors(int d);
	void setHasSunroof(bool s);
	void setHasLeatherSeats(bool l);

};



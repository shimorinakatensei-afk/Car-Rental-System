#pragma once
#include "Vehicle.h"
using namespace std;

//SUV subclass of Vehicle

class SUV : public Vehicle {
private:
	int seatingCapacity;
	bool has4WD;
	bool hasRoofRack;
	bool hasTowPackage;
public:
	SUV(int id, const string& brand, const string& model, int year, const string& color, int seatingCapacity = 7, bool has4WD = false,bool hasRoofRack = false, bool hasTowPackage = false, float mileage = 0.0f);
	~SUV() override;

	//Overriding Pure virtual functions
	float getRentalRate() const override;
	string getType() const override;
	void displayInfo() const override;
	string toCSV() const override;

	//Getters
	int getSeatingCapacity() const;
	bool getHas4WD() const;
	bool getHasRoofRack() const;
	bool getHasTowPackage() const;

	//Setters
	void setSeatingCapacity(int s);
	void setHas4WD(bool w);
	void setHasRoofRack(bool r);
	void setHasTowPackage(bool t);
};



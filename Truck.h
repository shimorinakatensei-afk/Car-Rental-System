#pragma once
#include "Vehicle.h"
using namespace std;

class Truck : public Vehicle {
private:
	//Private attributes here
	float cargoCapacityTons;
	bool hasTrailerHitch;
	bool isExtendedCab;
	float bedLengthFeet;
public:
	//Constructor and Distructor
	Truck(int id, const string& brand, const string& model, int year, const string& color, float cargoCapacityTons = 1.0f, bool hasTrailerHitch = false, bool isExtendedCab = false, float bedLengthFeet = 6.5f, float mileage = 0.0f);
	
	//Distructor
	~Truck() override;

	//Override pure virtual function
	float getRentalRate() const override;
	string getType() const override;
	void displayInfo() const override;
	string toCSV() const override;

	//Getters
	float getCargoCapacityTons() const;
	bool getHasTrailerHitch() const;
	bool getIsExtendedCab() const;
	float getBedLengthFeet() const;

	//Setters
	void setCargoCapacityTons(float c);
	void setHasTrailerHitch(bool h);
	void setIsExtendedCab(bool e);
	void setBedLengthFeet(float b);
	
};

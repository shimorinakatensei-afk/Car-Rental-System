#pragma once
#include <string>
#include <iostream>
using namespace std;

class Booking {
private:
	int bookingId;
	int customerId;
	int vehicleId;
	string customerName;
	string vehicleName;
	//format will be year/month/day
	string startDate;
	string endDate;
	int numDays;
	float dailyRate;
	float totalCost;
	//Active completed or cancelled
	string status;
	string paymentMethod;

	static int nextId;

public:
	//COnstructor and Distructor

	Booking(int  customerId, int vehicleId, const string& customerName, const string& vehicleName, const string& startDate, const string& endDate, float dailyRate, const string& paymentMethod = "Cash");
	~Booking();

	//Getters
	int  getBookingId() const;
	int getCustomerId() const;
	int getVehicleId() const;
	string getCustomerName() const;
	string getVehicleName() const;
	string getStartDate() const;
	string getEndDate() const;
	int getNumDays() const;
	float getDailyRate() const;
	float getTotalCost() const;
	string getStatus() const;
	string getPaymentMethod() const;

	//Setters

	void setStatus(const string& s);
	void setPaymentMethod(const string& pay);

	//Methods

	float calculateCost() const;
	int calculateNumDays() const;
	void displayBooking() const;
	string toCSV() const;

	//overloading operator;
	bool operator==(const Booking& other) const;
	bool operator< (const Booking& other) const;
	bool operator> (const Booking& other) const;

	friend ostream& operator<<(ostream& os, const Booking& b);

};

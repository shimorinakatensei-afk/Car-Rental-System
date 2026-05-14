#pragma once
#include "Vehicle.h"
#include "Sedan.h"
#include "SUV.h"
#include "Truck.h"
#include "Admin.h"
#include "Customer.h"
#include "Booking.h"
#include "Exceptions.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RentalManager {
private:
	//Only one Copy exist for the whole program 

	static vector<Admin*> admins;
	static vector<Vehicle*> fleet;
	static vector<Customer*> customers;
	static vector<Booking*> bookings;
	static int totalActiveRentals;
public:
	//Vehicle Management

	static void   addAdmin(Admin* a);
	static Admin* findAdminByEmail(const string& email);
	static void addVehicle(Vehicle* v);
	static void removeVehicle(int vehicleId);
	static void displayAllVehicles();
	static void displayAvailableVehicle();
	static Vehicle* findVehicle(int VehicleId);

	//Search Vehicle so Function overloading (same anme but different parameters)
	
	static vector<Vehicle*> searchByType(const string& type);
	static vector<Vehicle*> searchByMaxPrice(float maxPrice);
	static vector<Vehicle*> searchByType(const string& type, float maxPrice);

	//Customer management
	
	static void addCustomer(Customer* c);
	static void removeCustomer(int customerId);
	static void displayAllCustomers();
	static Customer* findCustomer(int customerId);
	static Customer* findCustomerByEmail(const string& email);
	

	//Booking management
	static Booking* makeBooking(int customerId, int vehicleId, const string& startDate, const string& endDate, const string& paymentMethod = "Cash");
	static void returnVehicle(int bookingId);
	static void cancelBooking(int bookingId);
	static void displayAllBookings();
	static void displayActiveBooking();
	static void displayBookingByCustomer(int customerId);
	static Booking* findBooking(int bookingId);

	//Statistic

	static int getTotalActiveRentals();
	static float getTotalRevenue();
	//Files

	static void saveVehicleToFile(const string& filename);
	static void saveCustomerToFile(const string& filename);
	static void saveBookingToFile(const string& filename);
	static void loadVehicleFromFile(const string& filename);
	static void loadCustomerFromFile(const string& filename);
	static void loadBookingFromFile(const string& filename);

	//Free dynamic memory

	static void clear();
};

#include <iostream> 
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Rentalmanager.h"

using namespace std;

vector<Admin*> RentalManager::admins;

//Add an admin

void RentalManager::addAdmin(Admin* a) {
	admins.push_back(a);
}

//static members definition must be defined outside the class in .cpp file
vector <Vehicle*> RentalManager::fleet;
vector <Customer*> RentalManager::customers;
vector <Booking*> RentalManager::bookings;
int RentalManager::totalActiveRentals = 0;

//Vehicle Management
void RentalManager::addVehicle(Vehicle* v) {
	if (v == nullptr) {
		throw InvalidInputException("Vehicle cannot be null");
	}
	//check for duplicate Id
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getVehicleId() == v->getVehicleId()) {
			throw InvalidInputException("Vehicle with that id is already exists");
		}
	}
	fleet.push_back(v);
	cout << "Vehicle added: " << v->getFullName() << endl;
}

void RentalManager::removeVehicle(int vehicleId) {
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getVehicleId() == vehicleId) {
			if (!fleet[i]->getIsAvailable()) {
				throw InvalidInputException("Cannot remove a vehicle that is currently rented.");
			}
			delete fleet[i];
			fleet.erase(fleet.begin() + i);
			cout << "Vehicle removed successfully" << endl;
			return;
		}
	}
	throw VehicleNotFoundException(vehicleId);
}

Vehicle* RentalManager::findVehicle(int vehicleId) {
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getVehicleId() == vehicleId) {
			return fleet[i];
		}
	}
	throw VehicleNotFoundException(vehicleId);
}

void RentalManager::displayAllVehicles() {
	if (fleet.empty()) {
		cout << "No vehicles are found" << endl;
		return;
	}
	cout << "==== All Vehiles ====" << endl;
	for (int i = 0; i < fleet.size(); i++) {
		fleet[i]->displayInfo();
	}
}

void RentalManager::displayAvailableVehicle() {
	cout << "=== Available Vehicles ===" << endl;
	bool found = false;
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getIsAvailable()) {
			fleet[i]->displayInfo();
			found = true;
		}
	}
	if (!found) {
		cout << "No Vehicles found." << endl;
	}
}

//Search vehicles functions overloading
vector<Vehicle*> RentalManager::searchByType(const string& type) {
	vector<Vehicle*> result;
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getType() == type && fleet[i]->getIsAvailable()) {
			result.push_back(fleet[i]);
		}
	}
	return result;
 }


//Search and Admin by email

Admin* RentalManager::findAdminByEmail(const string& email) {
	for (int i = 0; i < admins.size(); i++) {
		if (admins[i]->getEmail() == email)
			return admins[i];
	}
	throw InvalidInputException("No admin found with email: " + email);
}

//search my Max price only.

vector<Vehicle*> RentalManager::searchByMaxPrice(float maxPrice) {
	vector<Vehicle*> result;
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getRentalRate() <= maxPrice && fleet[i]->getIsAvailable()) {
			result.push_back(fleet[i]);
		}
	}
	return result;
}

//Search by Type and by Max price 

vector<Vehicle*> RentalManager::searchByType(const string& type, float maxPrice) {
	vector<Vehicle*> result;
	for (int i = 0; i < fleet.size(); i++) {
		if (fleet[i]->getType() == type && fleet[i]->getRentalRate() <= maxPrice && fleet[i]->getIsAvailable()) {
			result.push_back(fleet[i]);
		}
	}
	return result;
}

//Customer Management
void RentalManager::addCustomer(Customer* c) {
	if (c == nullptr) {
		throw InvalidInputException("Customer cannot be null");
	}

	//Check for duplication emails

	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getEmail() == c->getEmail()) {
			throw InvalidInputException("Customer with this email is already exists.");
		}
	}

	customers.push_back(c);
	cout << "Customer added: " << c->getName() << endl;
}

void RentalManager::removeCustomer(int customerId) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getPersonId() == customerId) {
			delete customers[i];
			customers.erase(customers.begin() + i);
			cout << "Customer remover successfully." << endl;
			return;
		}
	}
	throw CustomerNotFoundException(customerId);
}

Customer* RentalManager::findCustomer(int customerId) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getPersonId() == customerId) {
			return customers[i];
		}
	}
	throw CustomerNotFoundException(customerId);
}

Customer* RentalManager::findCustomerByEmail(const string& email) {
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i]->getEmail() == email) {
			return customers[i];
		}
	}
	throw InvalidInputException("Customer with email: " + email + " not Found.");
}

void  RentalManager::displayAllCustomers() {
	if (customers.empty()) {
		cout << "No customer registered" << endl;
		return;
	}
	cout << "=== All Customers ===" << endl;
	for (int i = 0; i < customers.size(); i++) {
		customers[i]->display();
	}
}

//Booking management

Booking* RentalManager::makeBooking(int customerId, int vehicleId, const string& startDate, const string& endDate, const string& paymentMethod) {
	//find customer and vehicle and if its not found then throw the Exception

	Customer* customer = findCustomer(customerId);
	Vehicle* vehicle = findVehicle(vehicleId);

	//check if the customer is banned

	if (customer->getIsBanned()) {
		throw InvalidInputException("This Customer is currently banned from making bookings.");
	}
	//Check if vehicle is availabe
	if (!vehicle->getIsAvailable()) {
		throw InvalidInputException(vehicle->getFullName());
	}

	//Create a booking
	Booking* booking = new Booking(customerId, vehicleId, customer->getName(), vehicle->getFullName(), startDate, endDate, vehicle->getRentalRate(), paymentMethod);
	//Update  vehicle availability

	vehicle->setAvailability(false);
	//link booking to customer
	customer->addBookingId(booking->getBookingId());

	//Add loyalty point , one point per day
	customer->addLoyaltyPoints(booking->getNumDays());

	//Store Booking and update counter
	bookings.push_back(booking);
	totalActiveRentals++;

	cout << "Booking created successfully! \nBookind Id: #" << booking->getBookingId() << endl;
	return booking;
}

void RentalManager::returnVehicle(int bookingId) {
	Booking* booking = findBooking(bookingId);

	if (booking->getStatus() != "Active") {
		throw InvalidInputException("This booking is not active");
	}

	// Now booking is completed
	booking->setStatus("Completed");

	// Make vehicle available again
	Vehicle* vehicle = findVehicle(booking->getVehicleId());
	vehicle->setAvailability(true);

	totalActiveRentals--;

	cout << "Vehicle returned successfully. Booking #" << bookingId << " completed." << endl;
}

void RentalManager::cancelBooking(int bookingId) {

	Booking* booking = findBooking(bookingId);
	if (booking->getStatus() != "Active") {
		throw InvalidInputException("Only active bookings can be cancelled");
	}

	// Mark booking as cancelled

	booking->setStatus("Cancelled");

	// Change vehicles status to available again
	Vehicle* vehicle = findVehicle(booking->getVehicleId());

	vehicle->setAvailability(true);

	// Remove booking from customer

	Customer* customer = findCustomer(booking->getCustomerId());
	customer->removeBookingId(bookingId);
	totalActiveRentals--;

	cout << "Booking #" << bookingId << " cancelled successfully." << endl;
}

Booking* RentalManager::findBooking(int bookingId) {
	for (int i = 0; i < bookings.size(); i++) {
		if (bookings[i]->getBookingId() == bookingId) {
			return bookings[i];
		}
	}
	throw BookingNotFoundException(bookingId);
}

void RentalManager::displayAllBookings() {

	if (bookings.empty()) {
		cout << "No bookings found." << endl;
		return;
	}

	cout << "==== All Bookings ====" << endl;
	for (int i = 0; i < bookings.size(); i++) {
		bookings[i]->displayBooking();
	}
}

void RentalManager::displayActiveBooking() {

	cout << "==== Active Bookings ====" << endl;
	bool found = false;

	for (int i = 0; i < bookings.size(); i++) {
		if (bookings[i]->getStatus() == "Active") {
			bookings[i]->displayBooking();
			found = true;
		}
	}
	if (!found)
		cout << "No active bookings." << endl;
}



void RentalManager::displayBookingByCustomer(int customerId) {
	cout << "==== Booking for Customer #" << customerId << " ====" << endl;
	bool found = false;
	for (int i = 0; i < bookings.size(); i++) {
		if (bookings[i]->getCustomerId() == customerId) {
			bookings[i]->displayBooking();
			found = true;
		}
	}
	if (!found)
		cout << "No bookings found for this customer." << endl;
}



//Statistics

int RentalManager::getTotalActiveRentals() {
	return totalActiveRentals;
}



float RentalManager::getTotalRevenue() {
	float total = 0.0f;
	for (int i = 0; i < bookings.size(); i++) {
		if (bookings[i]->getStatus() == "Completed") {
			total += bookings[i]->getTotalCost();
		}
	}
	return total;
}

//File to save the data

void RentalManager::saveVehicleToFile(const string& filename) {

	ofstream file(filename);
	if (!file.is_open()) {
		throw FileIOException(filename);
	}

	for (int i = 0; i < fleet.size(); i++) {
		file << fleet[i]->toCSV() << endl;
	}

	file.close();
	cout << "Vehicles saved to " << filename << endl;
}

void RentalManager::saveCustomerToFile(const string& filename) {


	ofstream file(filename);
	if (!file.is_open()) {
		throw FileIOException(filename);
	}

	for (int i = 0; i < customers.size(); i++) {
		file << customers[i]->toCSV() << endl;
	}

	file.close();
	cout << "Customers saved to " << filename << endl;
}

void RentalManager::saveBookingToFile(const string& filename) {



	ofstream file(filename);
	if (!file.is_open()) {
		throw FileIOException(filename);
	}

	for (int i = 0; i < bookings.size(); i++) {
		file << bookings[i]->toCSV() << endl;
	}

	file.close();
	cout << "Bookings saved to " << filename << endl;
}



//File to Load the data

void RentalManager::loadVehicleFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		throw FileIOException(filename);
	}

	string type;
	while (getline(file, type)) {
		if (type.empty() || type == "---") {
			continue;
		}

		// Read shared fields one line each
		string idLine, brand, model, yearLine, color, mileageLine, availLine;
		getline(file, idLine);
		getline(file, brand);
		getline(file, model);
		getline(file, yearLine);
		getline(file, color);
		getline(file, mileageLine);
		getline(file, availLine);

		// Convert strings to numbers 
		int   id, year;
		float mileage;
		bool  available;
		stringstream(idLine) >> id;
		stringstream(yearLine) >> year;
		stringstream(mileageLine) >> mileage;
		stringstream(availLine) >> available;

		if (type == "Sedan") {
			string doorsLine, sunroofLine, leatherLine;
			getline(file, doorsLine);
			getline(file, sunroofLine);
			getline(file, leatherLine);

			int  doors;
			bool sunroof, leather;
			stringstream(doorsLine) >> doors;
			stringstream(sunroofLine) >> sunroof;
			stringstream(leatherLine) >> leather;

			Sedan* s = new Sedan(id, brand, model, year, color, doors, sunroof, leather, mileage);
			s->setAvailability(available);
			fleet.push_back(s);

		}
		else if (type == "SUV") {
			string seatsLine, wdLine, roofLine, towLine;
			getline(file, seatsLine);
			getline(file, wdLine);
			getline(file, roofLine);
			getline(file, towLine);

			int  seats;
			bool wd, roof, tow;
			stringstream(seatsLine) >> seats;
			stringstream(wdLine) >> wd;
			stringstream(roofLine) >> roof;
			stringstream(towLine) >> tow;

			SUV* s = new SUV(id, brand, model, year, color, seats, wd, roof, tow, mileage);
			s->setAvailability(available);
			fleet.push_back(s);

		}
		else if (type == "Truck") {
			string cargoLine, hitchLine, cabLine, bedLine;
			getline(file, cargoLine);
			getline(file, hitchLine);
			getline(file, cabLine);
			getline(file, bedLine);

			float cargo, bed;
			bool  hitch, cab;
			stringstream(cargoLine) >> cargo;
			stringstream(hitchLine) >> hitch;
			stringstream(cabLine) >> cab;
			stringstream(bedLine) >> bed;

			Truck* t = new Truck(id, brand, model, year, color, cargo, hitch, cab, bed, mileage);
			t->setAvailability(available);
			fleet.push_back(t);
		}
	}

	file.close();
	cout << "Vehicles loaded from " << filename << endl;
}

void RentalManager::loadCustomerFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		throw FileIOException(filename);
	}

	string idLine;
	while (getline(file, idLine)) {
		if (idLine.empty() || idLine == "---") {
			continue;
		}

		string name, email, phone, address, license, password;
		string pointsLine, bannedLine, sep;

		getline(file, name);
		getline(file, email);
		getline(file, phone);
		getline(file, address);
		getline(file, license);
		getline(file, password);
		getline(file, pointsLine);
		getline(file, bannedLine);
		getline(file, sep);  
		
		// read "---" separator

		int  id;
		bool banned;
		stringstream(idLine) >> id;
		stringstream(bannedLine) >> banned;

		Customer* c = new Customer(id, name, email, phone, license, password, address);
		if (banned) c->setIsBanned(true);
		customers.push_back(c);
	}

	file.close();
	cout << "Customers loaded from " << filename << endl;
}


void RentalManager::loadBookingFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open())
		throw FileIOException(filename);

	string bookingIdLine;
	while (getline(file, bookingIdLine)) {
		if (bookingIdLine.empty() || bookingIdLine == "---") continue;

		string customerIdLine, vehicleIdLine;
		string customerName, vehicleName;
		string startDate, endDate;
		string dailyRateLine, totalCostLine;
		string status, paymentMethod, sep;

		getline(file, customerIdLine);
		getline(file, vehicleIdLine);
		getline(file, customerName);
		getline(file, vehicleName);
		getline(file, startDate);
		getline(file, endDate);
		getline(file, dailyRateLine);
		getline(file, totalCostLine);
		getline(file, status);
		getline(file, paymentMethod);
		getline(file, sep);  // read "---" separator

		int   customerId, vehicleId;
		float dailyRate;
		stringstream(customerIdLine) >> customerId;
		stringstream(vehicleIdLine) >> vehicleId;
		stringstream(dailyRateLine) >> dailyRate;

		Booking* b = new Booking(customerId, vehicleId, customerName,vehicleName,startDate,endDate,dailyRate,paymentMethod);
		b->setStatus(status);
		bookings.push_back(b);
	}

	file.close();
	cout << "Bookings loaded from " << filename << endl;
}



//Clean all the dynamic memory 

void RentalManager::clear() {
	for (int i = 0; i < fleet.size(); i++) {
		delete fleet[i];
	}
	fleet.clear();

	for (int i = 0; i < customers.size(); i++) {
		delete customers[i];
	}
	customers.clear();

	for (int i = 0; i < bookings.size(); i++) {
		delete bookings[i];
	}
	bookings.clear();

	for (int i = 0; i < admins.size(); i++) {
		delete admins[i];
	}
	admins.clear();

	totalActiveRentals = 0;
	cout << "All data cleared." << endl;
}



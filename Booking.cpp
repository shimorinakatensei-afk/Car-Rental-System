#include "Booking.h"
#include "Exceptions.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int Booking::nextId = 1000;

//constructor
Booking::Booking(int         customerId,
    int         vehicleId,
    const string& customerName,
    const string& vehicleName,
    const string& startDate,
    const string& endDate,
    float         dailyRate,
    const string& paymentMethod)
    : bookingId(nextId++),
    customerId(customerId),
    vehicleId(vehicleId),
    customerName(customerName),
    vehicleName(vehicleName),
    startDate(startDate),
    endDate(endDate),
    dailyRate(dailyRate),
    status("Active"),
    paymentMethod(paymentMethod)
{
    // Validate inputs
    if (customerName.empty())
        throw InvalidInputException("Customer name cannot be empty");
    if (vehicleName.empty())
        throw InvalidInputException("Vehicle name cannot be empty");
    if (startDate.empty() || endDate.empty())
        throw InvalidDateException("Dates cannot be empty");
    if (startDate >= endDate)
        throw InvalidDateException("End date must be after start date");
    if (dailyRate <= 0)
        throw InvalidInputException("Daily rate must be greater than 0");

    // Calculate number of days and total cost
    numDays = calculateNumDays();
    totalCost = calculateCost();
}

//destrucotr
Booking::~Booking() {}


//  Private helper ,they will calculates number of days between two dates
int Booking::calculateNumDays() const {
    // Parse startDate and endDate (format: YYYY-MM-DD)
    int startYear = stoi(startDate.substr(0, 4));
    int startMonth = stoi(startDate.substr(5, 2));
    int startDay = stoi(startDate.substr(8, 2));

    int endYear = stoi(endDate.substr(0, 4));
    int endMonth = stoi(endDate.substr(5, 2));
    int endDay = stoi(endDate.substr(8, 2));

    // Days in each month (non-leap year)
    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // Count total days from year 0 for start and end
    int startTotal = startYear * 365 + startDay;
    for (int i = 0; i < startMonth - 1; i++)
        startTotal += daysInMonth[i];

    int endTotal = endYear * 365 + endDay;
    for (int i = 0; i < endMonth - 1; i++)
        endTotal += daysInMonth[i];

    int days = endTotal - startTotal;

    if (days <= 0)
        throw InvalidDateException("End date must be after start date");

    return days;
}

//Methods for ooking
float Booking::calculateCost() const {
    return dailyRate * numDays;
}

void Booking::displayBooking() const {
    cout << fixed << setprecision(2);
    cout << "================================" << endl;
    cout << "  Booking ID: #" << bookingId << endl;
    cout << "  Customer: " << customerName << " (ID: " << customerId << ")" << endl;
    cout << "  Vehicle: " << vehicleName << " (ID: " << vehicleId << ")" << endl;
    cout << "  Start Date: " << startDate << endl;
    cout << "  End Date : " << endDate << endl;
    cout << "  Days : " << numDays << endl;
    cout << "  Rate/Day : $" << dailyRate << endl;
    cout << "  Total Cost: $" << totalCost << endl;
    cout << "  Payment: " << paymentMethod << endl;
    cout << "  Status : " << status << endl;
    cout << "================================" << endl;
}

string Booking::toCSV() const {
    ostringstream ss;
    ss << bookingId << ","
        << customerId << ","
        << vehicleId << ","
        << customerName << ","
        << vehicleName << ","
        << startDate << ","
        << endDate << ","
        << numDays << ","
        << dailyRate << ","
        << totalCost << ","
        << status << ","
        << paymentMethod;
    return ss.str();
}

//Getters
int    Booking::getBookingId()  const {
    return bookingId;
}
int    Booking::getCustomerId() const {
    return customerId;
}
int    Booking::getVehicleId()  const { 
    return vehicleId;
}
string Booking::getCustomerName() const {
    return customerName;
}
string Booking::getVehicleName() const {
    return vehicleName;
}
string Booking::getStartDate() const {
    return startDate; 
}
string Booking::getEndDate() const {
    return endDate;
}
int    Booking::getNumDays() const { 
    return numDays;
}
float  Booking::getDailyRate() const {
    return dailyRate; 
}
float  Booking::getTotalCost() const {
    return totalCost;
}
string Booking::getStatus() const {
    return status; 
}
string Booking::getPaymentMethod() const {
    return paymentMethod; 
}

//Setters
void Booking::setStatus(const string& s) {
    if (s != "Active" && s != "Completed" && s != "Cancelled")
        throw InvalidInputException("Status must be Active, Completed or Cancelled");
    status = s;
}

void Booking::setPaymentMethod(const string& method) {
    if (method.empty())
        throw InvalidInputException("Payment method cannot be empty");
    paymentMethod = method;
}

// Operator Overloading
bool Booking::operator==(const Booking& other) const {
    return bookingId == other.bookingId;
}

bool Booking::operator<(const Booking& other) const {
    return startDate < other.startDate;
}

bool Booking::operator>(const Booking& other) const {
    return startDate > other.startDate;
}

ostream& operator<<(ostream& os, const Booking& b) {
    os << fixed << setprecision(2);
    os << "Booking#" << b.bookingId << " | " << b.customerName << " | " << b.vehicleName << " | " << b.startDate << " -> " << b.endDate<< " | $" << b.totalCost
        << " | " << b.status;
    return os;
}
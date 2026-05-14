#pragma once
#include <stdexcept>	
#include <string>

using namespace std;


//Base exception for the Rental Systeme

class RentalException : public runtime_error {
public:
	explicit RentalException(const string& msg) : runtime_error(msg) {}
};

//Vehicle exception
class VehicleNotFoundException : public RentalException {
public:
	explicit VehicleNotFoundException(int id) : RentalException("No Vehicle found with ID: " + to_string(id)) {}
};

class VehicleNotAvailableException : public RentalException {
public:
	explicit VehicleNotAvailableException(const string& vehicleName) : RentalException("Vehicle: " + vehicleName + "is not available for rent."){}
};	

//Customer exception

class CustomerNotFoundException : public RentalException {
public:
	explicit CustomerNotFoundException(int id) : RentalException("No Customer found with ID: " + to_string(id)) {}
};

class InvalidCredentialsException : public RentalException {
public:
	InvalidCredentialsException() : RentalException("Incorrect Mail or Password") {}
};

//Booking Exceptions

class BookingNotFoundException : public RentalException {
public:
	explicit BookingNotFoundException(int id) : RentalException("No booking found with ID: " + to_string(id)) {}
};

class InvalidDateException : public RentalException {
public:
	explicit InvalidDateException(const string& detail) : RentalException("Invalid date: " + detail) {}
};

//Payment exception

class PaymentFailedException : public RentalException {
public:
	explicit PaymentFailedException(const string& reason) : RentalException("Payment Failed: " + reason) {}
};

//General Input (aka file exceptions)

class InvalidInputException : public RentalException {
public:
	explicit InvalidInputException(const string& field) : RentalException("Invalid Input " + field) {}
};

class FileIOException : public RentalException {
public:
	explicit FileIOException(const string& filename) : RentalException("Could not open i file " + filename) {}
};
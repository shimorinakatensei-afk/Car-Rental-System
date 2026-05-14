#include <iostream>
#include <limits>
#include "RentalManager.h"
#include "Exceptions.h"

using namespace std;

//FUnctions (helper)
void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void printHeader(const string& title) {
    cout << "========================================" << endl;
    cout << "  " << title << endl;
    cout << "========================================" << endl;
}

//Load data

void loadSampleData() {
    // Vehicles
    RentalManager::addVehicle(new Sedan(1, "Toyota", "Camry", 2022, "White", 4, true, true, 5000));
    RentalManager::addVehicle(new Sedan(2, "Honda", "Civic", 2021, "Black", 4, false, false, 12000));
    RentalManager::addVehicle(new SUV(3, "Ford", "Explorer", 2023, "Blue", 7, true, true, false, 3000));
    RentalManager::addVehicle(new SUV(4, "Toyota", "RAV4", 2022, "Red", 5, false, false, false, 8000));
    RentalManager::addVehicle(new Truck(5, "Ford", "F-150", 2021, "Gray", 2.0f, true, true, 6.5f, 15000));
    RentalManager::addVehicle(new Truck(6, "Chevy", "Silverado", 2023, "Black", 1.5f, false, false, 6.0f, 5000));

    // Customers
    RentalManager::addCustomer(new Customer(101, "Roman Kim", "roman@mail.com", "+998901234567", "LIC-001", "pass123"));
    RentalManager::addCustomer(new Customer(102, "Oybek Nortoji", "oybek@mail.com", "+998909876543", "LIC-002", "pass456"));
    RentalManager::addCustomer(new Customer(103, "Nurjan Serjanov", "nurjan@mail.com", "+998905556677", "LIC-003", "pass789"));

    // Admin
    RentalManager::addAdmin(new Admin(1, "RomanKA", "noname@gmail.com", "+82828288282", "ADMIN-001", "hiAWolrd!"));
}

//Customer Menu

void showCustomerMenu(Customer* customer) {
    int choice = 0;

    while (true) {
        clearScreen();
        printHeader("CUSTOMER MENU — " + customer->getName());
        cout << "  Loyalty Points : " << customer->getLoyaltyPoints() << endl;
        cout << "1. Browse Available Vehicles" << endl;
        cout << "2. Search Vehicles by Type" << endl;
        cout << "3. Search Vehicles by Max Price" << endl;
        cout << "4. Make a Booking" << endl;
        cout << "5. View My Bookings" << endl;
        cout << "6. Return a Vehicle" << endl;
        cout << "7. Cancel a Booking" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            printHeader("AVAILABLE VEHICLES");
            RentalManager::displayAvailableVehicle();
            pauseScreen();

        }
        else if (choice == 2) {
            clearScreen();
            printHeader("SEARCH BY TYPE");
            string type;
            cout << "Enter type (Sedan / SUV / Truck): ";
            cin >> type;

            vector<Vehicle*> results = RentalManager::searchByType(type);
            if (results.empty()) {
                cout << "No available vehicles of type: " << type << endl;
            }
            else {
                for (int i = 0; i < results.size(); i++)
                    results[i]->displayInfo();
            }
            pauseScreen();

        }
        else if (choice == 3) {
            clearScreen();
            printHeader("SEARCH BY MAX PRICE");
            float maxPrice;
            cout << "Enter maximum price per day: $";
            cin >> maxPrice;

            vector<Vehicle*> results = RentalManager::searchByMaxPrice(maxPrice);
            if (results.empty()) {
                cout << "No available vehicles under $" << maxPrice << "/day" << endl;
            }
            else {
                for (int i = 0; i < results.size(); i++)
                    results[i]->displayInfo();
            }
            pauseScreen();

        }
        else if (choice == 4) {
            clearScreen();
            printHeader("MAKE A BOOKING");
            RentalManager::displayAvailableVehicle();

            int vehicleId;
            string startDate, endDate, paymentMethod;

            cout << "Enter Vehicle ID to book : "; cin >> vehicleId;
            cout << "Start Date (YYYY-MM-DD)  : "; cin >> startDate;
            cout << "End Date   (YYYY-MM-DD)  : "; cin >> endDate;
            cout << "Payment Method           : "; cin.ignore(); getline(cin, paymentMethod);

            try {
                Booking* b = RentalManager::makeBooking(
                    customer->getPersonId(), vehicleId,
                    startDate, endDate, paymentMethod
                );
                cout << "\nBooking confirmed!" << endl;
                b->displayBooking();
            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 5) {
            clearScreen();
            printHeader("MY BOOKINGS");
            RentalManager::displayBookingByCustomer(customer->getPersonId());
            pauseScreen();

        }
        else if (choice == 6) {
            clearScreen();
            printHeader("RETURN A VEHICLE");
            RentalManager::displayBookingByCustomer(customer->getPersonId());

            int bookingId;
            cout << "Enter Booking ID to return: ";
            cin >> bookingId;

            try {
                RentalManager::returnVehicle(bookingId);
            }
            catch (const RentalException& e) {
                cout << "[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 7) {
            clearScreen();
            printHeader("CANCEL A BOOKING");
            RentalManager::displayBookingByCustomer(customer->getPersonId());

            int bookingId;
            cout << "\nEnter Booking ID to cancel: ";
            cin >> bookingId;

            try {
                RentalManager::cancelBooking(bookingId);
            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 8) {
            cout << "Logging out. Goodbye, " << customer->getName() << "!" << endl;
            pauseScreen();
            break;

        }
        else {
            cout << "Invalid choice. Try again." << endl;
            pauseScreen();
        }
    }
}

//Admin Menu

void showAdminMenu(Admin* admin) {
    int choice = 0;

    while (true) {
        clearScreen();
        printHeader("ADMIN PANEL — " + admin->getName());
        cout << "  Role : " << admin->getRole() << endl;
        cout << "1. View All Vehicles" << endl;
        cout << "2. Add a Vehicle" << endl;
        cout << "3. Remove a Vehicle" << endl;
        cout << "4. View All Customers" << endl;
        cout << "5. View All Bookings" << endl;
        cout << "6. View Active Bookings" << endl;
        cout << "7. View Statistics" << endl;
        cout << "8. Save All Data to Files" << endl;
        cout << "9. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            printHeader("ALL VEHICLES");
            RentalManager::displayAllVehicles();
            pauseScreen();

        }
        else if (choice == 2) {
            clearScreen();
            printHeader("ADD A VEHICLE");
            cout << "1. Sedan" << endl;
            cout << "2. SUV" << endl;
            cout << "3. Truck" << endl;
            cout << "Select type: ";
            int type; cin >> type;

            int id, year; string brand, model, color; float mileage;
            cout << "Vehicle ID : "; cin >> id;
            cout << "Brand  : "; cin >> brand;
            cout << "Model: "; cin >> model;
            cout << "Year   : "; cin >> year;
            cout << "Color: "; cin >> color;
            cout << "Mileage (km): "; cin >> mileage;

            try {
                if (type == 1) {
                    int doors; bool sunroof, leather;
                    cout << "Num Doors: "; cin >> doors;
                    cout << "Sunroof (1/0): "; cin >> sunroof;
                    cout << "Leather (1/0): "; cin >> leather;
                    RentalManager::addVehicle(new Sedan(id, brand, model, year, color, doors, sunroof, leather, mileage));

                }
                else if (type == 2) {
                    int seats; bool wd, roof, tow;
                    cout << "Seats  : "; cin >> seats;
                    cout << "4WD  (1/0) : "; cin >> wd;
                    cout << "RoofRack(1/0): "; cin >> roof;
                    cout << "TowPkg (1/0) : "; cin >> tow;
                    RentalManager::addVehicle(new SUV(id, brand, model, year, color, seats, wd, roof, tow, mileage));

                }
                else if (type == 3) {
                    float cargo, bed; bool hitch, cab;
                    cout << "Cargo (tons) : "; cin >> cargo;
                    cout << "Hitch  (1/0): "; cin >> hitch;
                    cout << "ExtCab (1/0): "; cin >> cab;
                    cout << "Bed Length : "; cin >> bed;
                    RentalManager::addVehicle(new Truck(id, brand, model, year, color, cargo, hitch, cab, bed, mileage));
                }
                cout << "Vehicle added successfully!" << endl;
            }
            catch (const RentalException& e) {
                cout << "[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 3) {
            clearScreen();
            printHeader("REMOVE A VEHICLE");
            RentalManager::displayAllVehicles();

            int vehicleId;
            cout << "Enter Vehicle ID to remove: ";
            cin >> vehicleId;

            try {
                RentalManager::removeVehicle(vehicleId);
            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 4) {
            clearScreen();
            printHeader("ALL CUSTOMERS");
            RentalManager::displayAllCustomers();
            pauseScreen();

        }
        else if (choice == 5) {
            clearScreen();
            printHeader("ALL BOOKINGS");
            RentalManager::displayAllBookings();
            pauseScreen();

        }
        else if (choice == 6) {
            clearScreen();
            printHeader("ACTIVE BOOKINGS");
            RentalManager::displayActiveBooking();
            pauseScreen();

        }
        else if (choice == 7) {
            clearScreen();
            printHeader("STATISTICS");
            cout << "  Total Active Rentals : " << RentalManager::getTotalActiveRentals() << endl;
            cout << "  Total Revenue        : $" << RentalManager::getTotalRevenue() << endl;
            pauseScreen();

        }
        else if (choice == 8) {
            clearScreen();
            printHeader("SAVING DATA");
            try {
                RentalManager::saveVehicleToFile("vehicles.txt");
                RentalManager::saveCustomerToFile("customers.txt");
                RentalManager::saveBookingToFile("bookings.txt");
                cout << "\nAll data saved successfully!" << endl;
            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
            }
            pauseScreen();

        }
        else if (choice == 9) {
            cout << "\nLogging out. Goodbye, " << admin->getName() << "!" << endl;
            pauseScreen();
            break;

        }
        else {
            cout << "\nInvalid choice. Try again." << endl;
            pauseScreen();
        }
    }
}

//Login Screen

void showLoginScreen() {
    int choice = 0;

    while (true) {
        clearScreen();
        printHeader("CAR RENTAL MANAGEMENT SYSTEM");
        cout << "\n  1. Login as Customer" << endl;
        cout << "  2. Login as Admin" << endl;
        cout << "  3. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1) {
            clearScreen();
            printHeader("CUSTOMER LOGIN");
            string email, password;
            cout << "Email    : "; cin >> email;
            cout << "Password : "; cin >> password;

            try {
                Customer* customer = RentalManager::findCustomerByEmail(email);
                if (!customer->verifyPassword(password))
                    throw InvalidCredentialsException();
                if (customer->getIsBanned()) {
                    cout << "\n[Error] This account has been banned." << endl;
                    pauseScreen();
                    continue;
                }
                cout << "\nWelcome, " << customer->getName() << "!" << endl;
                pauseScreen();
                showCustomerMenu(customer);

            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
                pauseScreen();
            }

        }
        else if (choice == 2) {
            clearScreen();
            printHeader("ADMIN LOGIN");
            string email, password;
            cout << "Email    : "; cin >> email;
            cout << "Password : "; cin >> password;

            try {
                Admin* admin = RentalManager::findAdminByEmail(email);
                if (!admin->verifyPassword(password))
                    throw InvalidCredentialsException();
                cout << "\nWelcome, " << admin->getName() << "!" << endl;
                pauseScreen();
                showAdminMenu(admin);

            }
            catch (const RentalException& e) {
                cout << "\n[Error] " << e.what() << endl;
                pauseScreen();
            }

        }
        else if (choice == 3) {
            cout << "\nThank you for using Car Rental System. Goodbye!" << endl;
            break;

        }
        else {
            cout << "\nInvalid choice. Try again." << endl;
            pauseScreen();
        }
    }
}

//main

int main() {
    loadSampleData();
    showLoginScreen();
    RentalManager::clear();
    return 0;
}
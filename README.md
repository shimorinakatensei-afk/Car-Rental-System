# 🚗 Car Rental Management System

![C++](https://img.shields.io/badge/Language-C%2B%2B-blue?style=for-the-badge&logo=cplusplus)
![OOP](https://img.shields.io/badge/Paradigm-OOP-green?style=for-the-badge)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio-purple?style=for-the-badge&logo=visualstudio)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

> A fully interactive **Car Rental Management System** built in C++ using Object-Oriented Programming principles.  
> Developed for **Object Oriented Programming 2 (MSC1052)** — Inha University in Tashkent, Spring 2026.

---

## 📸 Screenshots

> **Login Screen**

![Login](https://placehold.co/800x400/1a1a2e/white?text=Login+Screen+-+Customer+%2F+Admin)

> **Customer Menu**

![Customer](https://placehold.co/800x400/16213e/white?text=Customer+Menu+-+Browse+%2F+Book+%2F+Return)

> **Admin Panel**

![Admin](https://placehold.co/800x400/0f3460/white?text=Admin+Panel+-+Manage+Fleet+%2F+Bookings)

---

## ✨ Features

### 👤 Customer
- Login with email and password
- Browse all available vehicles
- Search vehicles by **type** (Sedan / SUV / Truck)
- Search vehicles by **max price per day**
- Make a booking with custom dates and payment method
- View personal booking history
- Return a rented vehicle
- Cancel an active booking
- Earn **loyalty points** for every rental day

### 🔧 Admin
- Login with admin credentials
- View entire vehicle fleet
- Add new vehicles (Sedan / SUV / Truck)
- Remove vehicles from fleet
- View all registered customers
- View all bookings or active bookings only
- View system statistics (revenue, active rentals)
- Save all data to files

---

## 🏗️ Class Structure

```
Vehicle  (abstract)
├── Sedan
├── SUV
└── Truck

Person  (abstract)
├── Customer
└── Admin

Booking
RentalManager  (static — brain of the system)
Exceptions  (custom exception hierarchy)
```

---

## 🎓 OOP Concepts Covered

| Concept | Where Used |
|---|---|
| **Abstraction** | `Vehicle` and `Person` are abstract base classes |
| **Inheritance** | `Sedan`, `SUV`, `Truck` extend `Vehicle` — `Customer`, `Admin` extend `Person` |
| **Polymorphism** | `displayInfo()`, `getRentalRate()`, `getType()` behave differently per vehicle |
| **Encapsulation** | All attributes are `private` / `protected` with getters and setters |
| **Operator Overloading** | `==`, `<`, `>`, `<<` on `Vehicle` and `Booking` |
| **Function Overloading** | `searchByType()`, `searchByMaxPrice()`, `searchByType(type, price)` |
| **Static Members** | `RentalManager` fleet, customers, bookings — `Booking::nextId` |
| **Exception Handling** | Full custom exception hierarchy from `RentalException` |
| **File I/O** | Save and load vehicles, customers, bookings to `.txt` files |
| **Dynamic Memory** | `new` and `delete` managed through `RentalManager::clear()` |

---

## 🚀 How to Run

### Requirements
- Windows
- Visual Studio 2019 or later
- C++17 or later

### Steps

```bash
# 1. Clone the repository
git clone https://github.com/YOUR_USERNAME/CarRentalSystem.git

# 2. Open in Visual Studio
# File → Open → Project/Solution → select OOPpro.sln

# 3. Build
# Build → Build Solution (Ctrl + Shift + B)

# 4. Run
# Ctrl + F5
```

---

## 🔐 Default Login Credentials

### Customers
| Name | Email | Password |
|---|---|---|
| Roman Kim | roman@mail.com | pass123 |
| Oybek Nortoji | oybek@mail.com | pass456 |
| Nurjan Serjanov | nurjan@mail.com | pass789 |

### Admin
| Email | Password |
|---|---|
| admin@rental.com | admin123 |

---

## 📁 Project Structure

```
CarRentalSystem/
│
├── Exceptions.h          # Custom exception hierarchy
│
├── Vehicle.h / .cpp      # Abstract base class for vehicles
├── Sedan.h / .cpp        # Sedan — $45/day base rate
├── SUV.h / .cpp          # SUV — $75/day base rate
├── Truck.h / .cpp        # Truck — $95/day base rate
│
├── Person.h / .cpp       # Abstract base class for persons
├── Customer.h / .cpp     # Customer with booking history
├── Admin.h / .cpp        # Admin with fleet management access
│
├── Booking.h / .cpp      # Booking linking Customer to Vehicle
├── RentalManager.h / .cpp # Static manager — brain of the system
│
└── main.cpp              # Interactive menu-driven entry point
```

---

## 💰 Rental Rate Breakdown

| Vehicle | Base Rate | Add-ons |
|---|---|---|
| **Sedan** | $45/day | +$5 sunroof, +$8 leather seats |
| **SUV** | $75/day | +$15 4WD, +$5 roof rack, +$10 tow package |
| **Truck** | $95/day | +$20/ton above 1 ton, +$15 hitch, +$10 ext. cab |

---

## 👥 Team

| Student ID | Name | Section |
|---|---|---|
| U2510165 | Roman Kim | 004 |
| U2510170 | Nortojiyev Oybek | 004 |
| U2510172 | Serjanov Nurjan | 004 |

---

## 🏫 Course Info

- **University:** Inha University in Tashkent
- **Course:** Object Oriented Programming 2 (MSC1052)
- **Semester:** Spring 2026
- **Due Date:** 06.03.2026

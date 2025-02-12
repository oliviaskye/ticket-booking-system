#include <iostream>
#include <C:\ticket-booking-system\nlohmann\json.hpp>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
// #include <bits/stdc++.h>
#include <ios>
#include <typeinfo>
#include <limits>
#include <stdio.h>
// #include <C:\ticket-booking-system\sqlite\sqlite3.h>
using json = nlohmann::json;

const std::string dbFile = "records.json";
// const std::string films[4] = {"The Big Country", "Monty Python and the Holy Grail", "The Truman Show", "Bambi II"};
// void showings(){
//     std::cout << "Today's showings:\n";
//     int i = 1;
//     for (std::string film : films) {
//         std::cout << i << ": " << film << "\n";
//         i++;
//     };
//     std::cout << "-----------------------\n";
// };

struct booking {
    int idnum;
    std::string userName;
    std::string lastname;
    std::string film;
    bool booked;
};

class Film {
    std::string name;
    int length;
    int filmId;
};

class User {
    std::string name;
    int userId;
};

class Reservation {
    int filmId;
    int userId;
    int reservationId;
};

json loadRecords() {
    std::fstream file(dbFile);
    if (!file.is_open()) {
        return json::object();
    }
    json db;
    file >> db;
    return db;
}

// Function to save the JSON rcords to a file
void saveRecords(const json& db) {
    std::ofstream file(dbFile);
    file << db.dump(4); // Save with indentation for readability
}

// Function to list all available films
void showingNow(const json& db) {
    if (db.find("films") == db.end() || db["films"].empty()) {
        std::cout << "No films available.\n";
        return;
    }
    std::cout << "Available Films:\n----------------------\n";
    for (const auto& film : db["films"]) {
        std::cout << "ID: " << film["id"] << " - " << film["name"] << std::endl;
    }
}

// Function to add a reservation
void makeBooking(json& db) {
    std::cout << "Please enter a name for the reservation: \n";
    std::string userName;
    std::cin >> userName;

    int film_choice;
    int i = 0;
    while (i==0){
        showingNow(db);
        std::cout << "Which film would you like to reserve a ticket for? Enter ID:\n";
        bool filmExists = false;
        while (filmExists == false){
            for (const auto& film : db["films"]) {
                if (film["id"] == film_choice) {
                    filmExists = true;
                    break;
                }
            }
            if (!filmExists) {
                std::cout << "Invalid choice, select another film.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return;
            }
        }
        i=1;
        break;
    }

    // Create reservation entry
    json reservation;
    reservation["id"] = db["reservations"].size() + 1;
    reservation["user"] = userName;
    reservation["filmId"] = film_choice;
    db["reservations"].push_back(reservation);
    saveRecords(db);
    std::cout << "Ticket booked successfully.\n";
}

// void viewBooking(const json& db, int bookingId) {
//     bool bookingExists = false;
//     for (const auto& reservation : db["reservations"]) {
//         if (reservation["id"] == bookingId) {

//             bookingExists = true;
//             break;
//         }
//     }

// }

int main(){

    json db = loadRecords();
    if (db.find("films") == db.end()) {
        db["films"] = json::array({
            { {"id", 1}, {"name", "The Big Country"}, {"length", 165} },
            { {"id", 2}, {"name", "Monty Python and the Holy Grail"}, {"length", 91} },
            { {"id", 3}, {"name", "The Truman Show"}, {"length", 103} },
            { {"id", 4}, {"name", "Bambi II"}, {"length", 72} }
        });
        saveRecords(db);
    }

    int i = 0;
    while (i == 0){
        std::cout << "Ticket Booking \n";
        std::cout << "1. View showings \n";
        std::cout << "2. Book a ticket \n";
        std::cout << "3. View my bookings \n";
        std::cout << "4. Edit bookings \n";
        std::cout << "5. Exit \n";
        std::cout << "-----------------------\n";
        std::cout << "Choose a function (1-5): \n";

        int user_choice;
        std::cin >> user_choice;
        std::cout << "-----------------------\n";

        switch(user_choice){
            case 1:
                showingNow(db);
                break;
            case 2:
                makeBooking(db);
                break;
            case 3:
                std::cout << "run view booking";
                // viewBooking(db);
                break;
            case 4:
                std::cout << "run change booking";
                break;
            case 5:
                std::cout << "Goodbye!";
                i = 1;
                break;
            default:
                std::cout << "invalid input, try again" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    };

    return 0;
};

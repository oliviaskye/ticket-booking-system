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
    std::ifstream file(dbFile);
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
        int choice;
        std::cout << "which film would you like to reserve a ticket for? (1-4)\n";
        while (!(std::cin >> choice) || choice > 4 || choice < 1){
            std::cout << "invalid input, try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        film_choice = choice;
        i=1;
        break;
    }

    // Check if the film ID exists
    bool filmExists = false;
    for (const auto& film : db["films"]) {
        if (film["id"] == filmId) {
            filmExists = true;
            break;
        }
    }
    if (!filmExists) {
        std::cout << "Invalid choice, select another film.\n";
        return;
    }

    // booking user;
    // user.film = films[film_choice-1];
    // user.userName = userName;
    // user.lastname = lastname;
    // user.booked = true;

    // std::cout << "Successful ticket booking.\nInfo:\n name: " << user.userName << " " << user.lastname << "\n film: " << user.film << std::endl;
    // std::cout << "-----------------------\n";
    
    // Create reservation entry
    json reservation;
    reservation["id"] = db["reservations"].size() + 1;
    reservation["user"] = userName;
    reservation["filmId"] = filmId;
    db["reservations"].push_back(reservation);
    saveRecords(db);
    std::cout << "Ticket booked successfully. Info:" << userName << "\n";
}

void viewBooking(const json& db, int bookingId) {
    bool bookingExists = false;
    for (const auto& reservation : db["reservations"]) {
        if (reservation["id"] == bookingId) {
            
            bookingExists = true;
            break;
        }
    }

}

int main(){

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
                showings();
                break;
            case 2: 
                makeBooking();
                break;
            case 3:
                viewBooking();
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
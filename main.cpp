#include <iostream>
#include <C:\ticket-booking-system\nlohmann\json.hpp>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <ios>
#include <typeinfo>
#include <limits>
#include <stdio.h>
using json = nlohmann::json;

const std::string dbFile = "records.json";

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
        std::cin >> film_choice;
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
    int bookingId = db["reservations"].size() + 1;
    reservation["id"] = bookingId;
    reservation["user"] = userName;
    reservation["filmId"] = film_choice;
    db["reservations"].push_back(reservation);
    saveRecords(db);
    std::cout << "Ticket booked successfully. Your booking ID is:" << bookingId << std::endl;

}

void viewBooking(const json& db) {
    // json db = loadRecords();
    // json reservation;
    std::cout << "Please provide your booking ID:\n";
    int bookingId;
    std::cin >> bookingId;

    // bool bookingExists = false;
    for (const auto& reservation : db["reservations"]) {
        if (reservation["id"] == bookingId) {
            // bookingExists = true;
            for (const auto& film : db["films"]){
                if (reservation["filmId"] == film["id"]){
                    std::cout << "Ticket booked for" << reservation["name"] << "for a showing of" << film["name"];
                    break;
                }
            }
            break;
        }
        else{
            std::cout << "No reservation for this id." << std::endl;
        }
    }
}

int main(){

    json db = loadRecords();
    if (db.find("films") == db.end()) {
        db["films"] = json::array({
            {{"id", 1}, {"name", "The Big Country"}},
            {{"id", 2}, {"name", "Monty Python and the Holy Grail"}},
            {{"id", 3}, {"name", "The Truman Show"}},
            {{"id", 4}, {"name", "Bambi II"}}
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
                viewBooking(db);
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

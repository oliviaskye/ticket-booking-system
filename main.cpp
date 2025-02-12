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

const std::string dbFile = "records.json"; // File path for storing data
const std::string films[4] = {"The Big Country", "Monty Python and the Holy Grail", "The Truman Show", "Bambi II"};

struct booking {
    int idnum;
    std::string firstname;
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
        return json::object(); // Return empty JSON object if file doesn't exist
    }
    json db;
    file >> db;
    return db;
}

// Function to save the JSON saveRecords to a file
void saveRecords(const json& db) {
    std::ofstream file(dbFile);
    file << db.dump(4); // Save with indentation for readability
}

// Function to list all available films
// void listFilms(const json& db) {
//     if (db.find("films") == db.end() || db["films"].empty()) {
//         std::cout << "No films available.\n";
//         return;
//     }
//     std::cout << "Available Films:\n----------------------\n";
//     for (const auto& film : db["films"]) {
//         std::cout << "ID: " << film["id"] << " - " << film["name"] << " (" << film["length"] << " min)\n";
//     }
// }

// Function to add a reservation
void makeReservation(json& db, const std::string& user_name, int film_id) {
    if (db.find("films") == db.end() || db["films"].empty()) {
        std::cout << "No films available for reservation.\n";
        return;
    }
    
    // Check if the film ID exists
    bool filmExists = false;
    for (const auto& film : db["films"]) {
        if (film["id"] == film_id) {
            filmExists = true;
            break;
        }
    }
    if (!filmExists) {
        std::cout << "Invalid film ID.\n";
        return;
    }
    
    // Create reservation entry
    json reservation;
    reservation["id"] = db["reservations"].size() + 1;
    reservation["user"] = user_name;
    reservation["film_id"] = film_id;
    db["reservations"].push_back(reservation);
    saveRecords(db);
    std::cout << "Reservation successful for " << user_name << "!\n";
}

void showings(){
    std::cout << "Today's showings:\n";
    int i = 1;
    for (std::string film : films) {
        std::cout << i << ": " << film << "\n";
        i++;
    };
    std::cout << "-----------------------\n";
};

void makeBooking(){

    showings();
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

    std::cout << "Please enter your first name: \n";
    std::string firstname;
    std::cin >> firstname;

    std::cout << "Please enter your last name: \n";
    std::string lastname;
    std::cin >> lastname;

    booking user;
    user.film = films[film_choice-1];
    user.firstname = firstname;
    user.lastname = lastname;
    user.booked = true;

    std::cout << "Successful ticket booking.\nInfo:\n name: " << user.firstname << " " << user.lastname << "\n film: " << user.film << std::endl;
    std::cout << "-----------------------\n";

};

void viewBooking() {

    // json j = "{ \"happy\": true, \"pi\": 3.141 }"_json;
    // std::cout << j << std::endl;
    // std::cout << typeid(j).name() << std::endl;
    // std::string s = j.dump();
    // std::cout << s << std::endl;
    // std::cout << typeid(s).name() << std::endl;

    //using namespace ns;
    // std::ifstream f("records.jsonl");
    // json data = json::parse(f);
    // std::cout << data << std::endl;
    // f.close();
    try {
        std::ifstream f("records.json");
        json data = json::parse(f);
        std::cout << data << std::endl;

        f.close();
        //std::fstream f("records.jsonl");
        // std::cout << f << std::endl;
        // std::string s = f.dump();
        // f.close();

        //TODO: return
       //std::fstream lines("C:\ticket booking\records.json", std::ios::in);
        // std::cout << lines << std::endl;

        //std::ifstream jsonFile("records.jsonl", std::ios::in);
        //json parsed_json = json::parse(jsonFile);
        //std::cout << parsed_json;

        //std::stringstream lines;
        //lines << file;

        //std::fstream s;
        //s.open("records.jsonl");
        //std::stringstream lines;
        //lines << s;
        //TODO: return
        //std::string line;
        //while(std::getline(lines, line))
        //{
          //  std::cout << json::parse(line) << std::endl;
        //}
    }
    catch (json::parse_error& e)
      {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
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

        //try {

            //if (user_choice){
              //  return user_choice;
            //}
            //else {
            //    throw "invalid choice";
            //}
        //}
        //catch (...){
            //continue;
        //};
        //while (true){
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
        //};
    };

    return 0;
};



#include <iostream> // Standard input-output library
#include <fstream> // File handling for JSON storage
#include <C:\ticket-booking-system\nlohmann\json.hpp> // JSON library for handling data
#include <string> // String library for handling text

using json = nlohmann::json; // Alias for JSON usage



int main() {
    json db = loadDatabase(); // Load database from JSON file

    // Ensure films exist in the database
    if (db.find("films") == db.end()) {
        db["films"] = json::array({
            { {"id", 1}, {"name", "The Big Country"}, {"length", 165} },
            { {"id", 2}, {"name", "Monty Python and the Holy Grail"}, {"length", 91} },
            { {"id", 3}, {"name", "The Truman Show"}, {"length", 103} },
            { {"id", 4}, {"name", "Bambi II"}, {"length", 72} }
        });
        saveRecords(db);
    }
    
    std::cout << "1. List Films\n2. Make Reservation\nChoose an option: ";
    int choice;
    std::cin >> choice;
    
    if (choice == 1) {
        listFilms(db);
    } else if (choice == 2) {
        std::string name;
        int film_id;
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter film ID: ";
        std::cin >> film_id;
        makeReservation(db, name, film_id);
    }
    return 0;
}

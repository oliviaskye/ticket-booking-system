#include <iostream>
#include <C:\ticket-booking-system\nlohmann\json.hpp>
//#include <C:\ticket-booking-system\makeBooking.cpp>
//#include <C:\ticket-booking-system\showings.cpp>
#include <exception>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
// #include <bits/stdc++.h>
#include <ios>
#include <typeinfo>
#include <limits>
#include <C:\ticket-booking-system\rapidjson\document.h>
#include <C:\ticket-booking-system\rapidjson\writer.h>
#include <C:\ticket-booking-system\rapidjson\stringbuffer.h>
#include <C:\ticket-booking-system\rapidjson\filereadstream.h>
#include <C:\ticket-booking-system\rapidjson\filewritestream.h>
#include <stdio.h>
#include <C:\ticket-booking-system\sqlite\sqlite3.h>

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

static int callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\n";
    }
    std::cout << "----------------------\n";
    return 0;
}

void initializeDB(sqlite3* &db) {
    const char* sql_users = "CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);";
    const char* sql_films = "CREATE TABLE IF NOT EXISTS Films (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT);";
    const char* sql_reservations = "CREATE TABLE IF NOT EXISTS Reservations (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, film_id INTEGER, FOREIGN KEY(user_id) REFERENCES Users(id), FOREIGN KEY(film_id) REFERENCES Films(id));";
    
    char* errMsg;
    sqlite3_exec(db, sql_users, 0, 0, &errMsg);
    sqlite3_exec(db, sql_films, 0, 0, &errMsg);
    sqlite3_exec(db, sql_reservations, 0, 0, &errMsg);
}

std::string films[4] = {"The Big Country", "Monty Python and the Holy Grail", "The Truman Show", "Bambi II"};

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

    std::cout << "Successful ticket booking.\nInfo:\n name: " << user.firstname << " " << user.lastname << "\n film: " << user.film << std::endl;
    std::cout << "-----------------------\n";

};

void viewBooking() {

}

int main(){

    sqlite3* db;
        if (sqlite3_open("reservations.db", &db)) {
            std::cerr << "Error opening database." << std::endl;
            return 1;
        }
    initializeDB(db);

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
    sqlite3_close(db);
    return 0;
};



// static int createDB(const char* s);
// static int createTable(const char* s);

// int main(){
//     const char* dir = "C:\ticket-booking-system\database\RECORDS.db";
//     createDB(dir);
//     createTable(dir);
//     sqlite3* DB;

//     return 0;
// }

// vers 1:
// void openDB(char* records, sqlite3* database)
// {
//     int opened = sqlite3_open("records.db", &database);
//     if(opened){ // check if opening the database is successful
//         std::cout << ("Database could not be opened %s \n", sqlite3_errmsg(database)) << std::endl;
//     } else {
//         std::cout << ("opened database successfuly \n") << std::endl;
//         db = database;
//     }
// }
// int main(int, char**){
//     char* records = "db.sqlite3";
//     openDB(records, db);

// }
// vers 2:
// int main(int argc, char* argv[]) {
//    sqlite3 *db;
//    char *zErrMsg = 0;
//    int rc;

//    rc = sqlite3_open("records.db", &db);

//    if( rc ) {
//       std::cout << (stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) << std::endl;
//       return(0);
//    } else {
//       std::cout << (stderr, "Opened database successfully\n") << std::endl;
//    }
//    sqlite3_close(db);
// }





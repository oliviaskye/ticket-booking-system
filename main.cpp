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
sqlite3* db;
// sqlite 3 db connection:
// open the database
void openDB(char* records, sqlite3* database)
{
    int opened = sqlite3_open("records.db", &database);
    if(opened){ // check if opening the database is successful
        std::cout << ("Database could not be opened %s \n", sqlite3_errmsg(database)) << std::endl;
    } else {
        std::cout << ("opened database successfuly \n") << std::endl;
         db = database;
    }
}
int main(int, char**){
    char* records = "db.sqlite3";
    openDB(records,  db);

}
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

using json = nlohmann::json;


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

    booking user;
    user.film = films[film_choice-1];
    user.firstname = firstname;
    user.lastname = lastname;
    user.booked = true;



    std::cout << "Successful ticket booking.\nInfo:\n name: " << user.firstname << " " << user.lastname << "\n film: " << user.film << std::endl;
    std::cout << "-----------------------\n";

};

void viewBooking() {

}

// int main(){
//     int i = 0;
//     while (i == 0){
//         std::cout << "Ticket Booking \n";
//         std::cout << "1. View showings \n";
//         std::cout << "2. Book a ticket \n";
//         std::cout << "3. View my bookings \n";
//         std::cout << "4. Edit bookings \n";
//         std::cout << "5. Exit \n";
//         std::cout << "-----------------------\n";
//         std::cout << "Choose a function (1-5): \n";

//         //try {

//             //if (user_choice){
//               //  return user_choice;
//             //}
//             //else {
//             //    throw "invalid choice";
//             //}
//         //}
//         //catch (...){
//             //continue;
//         //};
//         //while (true){
//         int user_choice;
//         std::cin >> user_choice;
//         std::cout << "-----------------------\n";
//         switch(user_choice){
//             case 1:
//                 showings();
//                 break;
//             case 2:
//                 makeBooking();
//                 break;
//             case 3:
//                 viewBooking();
//                 break;
//             case 4:
//                 std::cout << "run change booking";
//                 break;
//             case 5:
//                 std::cout << "Goodbye!";
//                 i = 1;
//                 break;
//             default:
//                 std::cout << "invalid input, try again" << std::endl;
//                 std::cin.clear();
//                 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//         }
//         //};
//     };

//     return 0;
// };




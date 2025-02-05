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
// sqlite3* db;
// sqlite 3 db connection:
// open the database
// void openDB(char* records, sqlite3* database)
// {
//     int opened = sqlite3_open("records.db", &database);
//     if(opened){ // check if opening the database is successful
//         std::cout << ("Database could not be opened %s \n", sqlite3_errmsg(database)) << std::endl;
//     } else {
//         std::cout << ("opened database successfuly \n") << std::endl;
//          db = database;
//     }
// }
// int main(int, char**){
//     char* records = "db.sqlite3";
//     openDB(records,  db);

// }
int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("records.db", &db);

   if( rc ) {
      std::cout << (stderr, "Can't open database: %s\n", sqlite3_errmsg(db)) << std::endl;
      return(0);
   } else {
      std::cout << (stderr, "Opened database successfully\n") << std::endl;
   }
   sqlite3_close(db);
}

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

// namespace ns {
    void to_json(json& j, const booking& user) {
        j = json{ {"first name", user.firstname}, {"last name", user.lastname}, {"film", user.film}, {"booked", user.booked} };
    };

    void from_json(const json& j, booking& user) {
        j.at("first name").get_to(user.firstname);
        j.at("last name").get_to(user.lastname);
        j.at("film").get_to(user.film);
        j.at("booked").get_to(user.booked);
    };
// }

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

    //user{films[film_choice-1], firstname, lastname, true};

    // attempt 1:
    //json j;
    //j["first name"] = user.firstname;
    //j["last name"] = user.lastname;
    //j["film"] = user.film;
    //j["booked"] = user.booked;

    // attempt 2:
    json j;
    to_json(j, user);

    std::fstream outfile;
    outfile.open("records.json", std::ios::app | std::ios::in);
    outfile << std::setw(4) << j << std::endl;
    //outfile >> data;
    outfile.close();

    std::ifstream f("records.json");
    json data = json::parse(f);
    std::cout << data << std::endl;
    f.close();


    //std::cout << j << std::endl;
    //{"film":films[film_choice-1],firstname":firstname,"lastname":lastname,"booked":true}

    //conversion: json -> booking

    //conversion: booking -> json
    //TODO: return section
    //json j = user;

    //std::ofstream outfile;
    //outfile.open("records.json", std::ios::app);
    //outfile << j << '\n';
    //outfile >> data;
    //outfile.close();
    //end return section

    //rapidjson test
    //using namespace rapidjson;
    //Document d;
    //d.SetObject();

    // Add data to the JSON document
    //d.AddMember("film", user.film, d.GetAllocator());
    //d.AddMember("firstname", user.firstname, d.GetAllocator());
    //d.AddMember("lastname", user.lastname, d.GetAllocator());
    //d.AddMember("booked", user.booked, d.GetAllocator());

    // Open the output file
    //std::ofstream file("records.json");

    // Write the JSON data to the file . buffer, sizeof(buffer)
    //FileWriteStream os(file);
    //Writer<FileWriteStream> writer(os);
    //d.Accept(writer);

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




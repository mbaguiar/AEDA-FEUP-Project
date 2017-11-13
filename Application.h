//
// Created by Mariana on 31/10/2017.
//

#ifndef AEDA_FEUP_PROJECT_APPLICATION_H
#define AEDA_FEUP_PROJECT_APPLICATION_H

#include <iostream>
#include <vector>
#include "Company.h"


using namespace std;

class Application {

private:
    Company company;
    bool passengersChanged;
    bool airplanesChanged;
    bool flightsChanged;
    string passengersFilepath;
    string airplanesFilepath;
    string flightsFilepath;

public:
    Application();

    //menus
    void mainMenu();
    void filesMenu();
    void passengersMenu();
    void airplanesMenu();
    void flightsMenu(Airplane *airplane);
    void bookingsMenu();

    //passenger fucntions
    void passengerShow();
    void passengerCreate();
    void passengerDelete();
    void passengerUpdateMenu();
    void printSummaryPassenger();
    Passenger * choosePassenger();
    void validPassenger(int id);
    void passengerUpdateName(Passenger * passenger);
    void passengerUpdateDateOfBirth(Passenger * passenger);
    void passengerUpdateJob(Passenger * passenger);
    void passengerUpdateNYear(Passenger * passenger);

    //airplane functions
    void airplaneShow();
    void airplaneCreate();
    void airplaneDelete();
    void airplaneUpdateMenu();
    void printSummaryAirplane();
    Airplane * chooseAirplane();
    void validAirplane(int id);
    void airplaneUpdateModel(Airplane * airplane);
    void airplaneUpdateCapacity(Airplane * airplane);


    void flightShow(Airplane * airplane);
    void flightCreate(Airplane * airplane);
    void flightDelete(Airplane * airplane);
    void flightUpdateMenu(Airplane * airplane);
    void printSummaryFlight(Airplane * airplane);
    Flight * chooseFlight(Airplane * airplane);
    void validFlight(int id);
    void flightUpdatePrice(Flight * flight);
    void flightUpdateDuration(Flight * flight);
    void flightAddPassenger(Flight * flight);
    void flightDeletePassenger(Flight * flight);
    void flightUpdateBuyer(Flight * flight);


};


#endif //AEDA_FEUP_PROJECT_APPLICATION_H

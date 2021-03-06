#ifndef AEDA_FEUP_PROJECT_COMPANY_H
#define AEDA_FEUP_PROJECT_COMPANY_H
/**
* @{
*
* Company class declaration
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include "helper.h"
#include "exceptions.h"
#include "Airplane.h"
#include "Technician.h"
#include <queue>
#include <cmath>
#include <unordered_set>
#include <utility>

using namespace std;

struct AirplaneCompare {
    bool operator()(Airplane *a1, Airplane *a2) {
        if (a1->getMaintenance().year == a2->getMaintenance().year) {
            if (a1->getMaintenance().month == a2->getMaintenance().month)
                return a1->getMaintenance().day < a2->getMaintenance().day;
            else return a1->getMaintenance().month < a2->getMaintenance().month;
        } else return a1->getMaintenance().year < a2->getMaintenance().year;
    }
};

struct TechnicianCompare {
    bool operator()(Technician *t1, Technician *t2) {
        return t1->getTimeWhenAvailable() > t2->getTimeWhenAvailable();
    }
};

typedef std::set<Airplane *, AirplaneCompare> AirplanesSet;

struct InactivePassengerHash {
    int operator()(const Passenger *p1) const {
        return static_cast<int>(hash<int>()(p1->getId()));
    }

    bool operator()(const Passenger *p1, const Passenger *p2) const {
        return p1->getId() == p2->getId();
    }
};

typedef unordered_set<Passenger *, InactivePassengerHash, InactivePassengerHash> inactivePassengersHT;

typedef priority_queue<Technician *, vector<Technician *>, TechnicianCompare> techniciansPriorityQueue;

/**
*	The Company class is the one that countains all the passengers, airplanes and flights information
*/
class Company {

    typedef void(Company::*Menu)(void);

private:
    /**
    * @brief string name of the company object
    */
    string name;
    /**
    * @brief vector with pointers to all the Airplanes of the company
    */
    AirplanesSet fleet;
    /**
    * @brief vector with pointers to all the Passengers of the company
    */
    vector<Passenger *> passengers;
    /**
     * @brief vector with pointers to all the Flights of the company
     */
    vector<Flight *> flights;
    /**
    * @brief vector with pointers to all of the past Flights of the company
    */
    vector<Flight *> pastFlights;
    /**
     * @brief priority queue that has all of the pointers to technicians of the company
     */
    techniciansPriorityQueue technicians;
    /**
     * @brief vector with pointers to all of the Bookings of the company
     */
    vector<Booking *> bookings;
    /**
     * @brief vector with pointers to all of the past Bookings of the company
     */
    vector<Booking *> pastBookings;
    /**
     * @brief Hash Table that holds all the inactive Passengers of the company
     */
    inactivePassengersHT inactivePassengers;
    /**
    * @brief bool passengersChanged is true when Passengers vector has changed and false otherwise
    */
    static bool passengersChanged;
    /**
    * @brief bool airplanesChanged is true when Airplanes vector has changed and false otherwise
    */
    static bool airplanesChanged;
    /**
     * @brief bool flightsChanged is true when Flights vector has changed and false otherwise
    */
    static bool flightsChanged;
    /**
     * @brief bool techniciansChanged is true when Technicians priority queue has changed and false otherwise
     */
    static bool techniciansChanged;

public:

    /**
     * @brief Default Constructor of a Company object
     */
    Company();

    /**
     * @brief Constructor of a Company object only defining its name
     * @param name string name
     */
    explicit Company(string name);

    /**
    * @brief identifier for an Airplane
    */
    static const string AIRPLANE_IDENTIFIER;
    /**
    * @brief identifier for a Flight
    */
    static const string FLIGHT_IDENTIFIER;
    /**
    * @brief identifier for a Passenger
    */
    static const string PASSENGER_IDENTIFIER;
    /**
     * @brief identifier for a Technician
     */
    static const string TECHNICIAN_IDENTIFIER;

    //get methods
    /**
    * @brief Used to get the name of a company
    * @return string name of a company
    */
    string getName() const;

    /**
    * @brief Gets the fleet of the company
    * @return vector <Airplane*> with the pointers to the Airplanes of the company
    */
    AirplanesSet getFleet() const;

    /**
    * @brief Gets a vector of pointers to the passengers of the company
    * @return vector <Passenger*> with the pointers to the Passengers of the company
    */
    vector<Passenger *> getPassengers() const;

    /**
     * @brief Gets the priority queue with all the technicians in the Company object
     * @return techniciansPriorityQueue
     */
    techniciansPriorityQueue getTechnicians() const;

    /**
     * @brief Gets if the priority queue of technicians has changed or not
     * @return True if the technicians priority queue has changed and false otherwise
     */
    bool getTechniciansChanged() const;

    /**
    * @brief Gets the flag that indicates wheather the vector Passengers changed
    * @return true if the Passengers vector has changed or false otherwise
    */
    bool getPassengersChanged() const;

    /**
    * @brief Gets the flag that indicates wheather the vector Fleet changed
    * @return true if the Fleet vector has changed or false otherwise
    */
    bool getAirplanesChanged() const;

    /**
    * @brief Gets the flag that indicates wheather the vector Flights changed
    * @return true if the Flights vector has changed or false otherwise
    */
    bool getFlightsChanged() const;

    //set methods
    /**
    * @brief Sets the name of the company to the passed parameter name
    * @param name string name
    */
    void setName(string name);

    /**
    * @brief Sets the fleet of the company to the passed parameter vector \<Airplane * \> fleet
    * @param fleet vector \< Airplane * \> fleet
    */
    void setFleet(AirplanesSet fleet);

    /**
    * @brief Removes the Passenger from the data member passengers
    * @param *passenger Passenger *passenger pointer to the Passenger object to be removed
    */
    void removePassenger(Passenger *passenger);

    /**
    * @brief Sets the pointers of the Passengers of the company to the passed parameter vector <Passenger*> passengers
    * @param passengers vector <Passenger*> passengers
    */
    void setPassengers(vector<Passenger *> passengers);

    /**
    * @brief Removes the passed Airplane of the company fleet
    * @param airplane Airplane airplane that indicates which Airplane to remove from the data member fleet of the company
    */
    void removeAirplane(Airplane *airplane);

    /**
    * @brief Searches the fleet for the passed argument id and return pointer to a Flight object
    * @param id unsigned int id
    * @return Flight * pointer to the Flight object
    */
    Flight *flightById(unsigned int id);

    /**
    * @brief Searches the passengers vector for the passed argument id and return pointer to the desired Passenger object
    * @param id unsigned int id
    * @return Passenger * pointer to the Passenger object
    */
    Passenger *passengerById(unsigned int id);

    /**
    * @brief Gets the flights of the Company
    * @return vector<Flight *> flights of the Company object
    */
    vector<Flight *> getFlights() const { return flights; }

    /**
   * @brief Prints the total information of a desired Passenger
   */
    void passengerShow();

    /**
     * @brief Creates a new Passenger and adds it to the Company vector passengers after validating the information
     */
    Passenger *passengerCreate();

    /**
     * @brief Deletes the pretended Passenger from the Company vector containing the passengers
     */
    void passengerDelete();

    /**
 * @brief Prints a summary of a Passenger object
 */
    void printSummaryPassenger();

    /**
     * @brief Searches the passengers vector for the id inserted by the user and returns the pretended Passenger
     * @return Passenger*
     */
    Passenger *choosePassenger();

    /**
     * @brief Checks if the id is in the vector of passengers, if it is an exception is thrown
     * @param id int id
     */
    void validPassenger(int id);

    /**
     * @brief Updates the name of the passenger passed as parameter to the one inserted by the user
     * @param *passenger Passenger *passenger
     */
    void passengerUpdateName(Passenger *passenger);

    /**
     * @brief Updates the date of birth of the passenger passed as parameter to the one inserted by the user
     * @param *passenger Passenger *passenger
     */
    void passengerUpdateDateOfBirth(Passenger *passenger);

    /**
     * @brief Updates the job of the passenger passed as parameter to the one inserted by the user
     * @param *passenger Passenger *passenger
     */
    void passengerUpdateJob(Passenger *passenger);

    /**
     * @brief Updates the average number of flights per year of the passenger passed as parameter to the one inserted by the user
     * @param *passenger Passenger *passenger
     */
    void passengerUpdateNYear(Passenger *passenger);

    /**
    * @brief Prints the total information of a desired Airplane
    */
    void airplaneShow();

    /**
    * @brief Creates a new Airplane and adds it to the Company vector fleet after validating the information
    */
    void airplaneCreate();

    /**
    * @brief Deletes the pretended Airplane from the Company vector containing the Airplanes
    */
    void airplaneDelete();

    /**
     * @brief Reschedule the time in which a maintenance will occur
     */
    void airplaneMaintenanceReschedule();

    /**
     * @brief Performs a Maintenance on an Airplane, it will use other functions and restart timetillAvaiable of a technician
     */
    void airplanePerformMaintenance();

    /**
    * @brief Prints a summary of an Airplane object
    */
    void printSummaryAirplane();

    /**
    * @brief Searches the Airplanes vector for the id inserted by the user and returns the pretended Airplane
    * @return Airplane*
    */
    Airplane *chooseAirplane();

    /**
    * @brief Checks if the id is in the vector of airplanes, if it is an exception is thrown
    * @param id int id
    */
    void validAirplane(int id);

    /**
    * @brief Updates the model of the Airplane passed as argument to the one inserted by the user
    * @param airplane Airplane * airplane
    */
    void airplaneUpdateModel(Airplane *airplane);

    /**
    * @brief Updates the capacity of the Airplane passed as argument to the one inserted by the user
    * @param airplane Airplane * airplane
    */
    void airplaneUpdateCapacity(Airplane *airplane);

    /**
     * @brief Changed the period in which a Maintenance will occur on a passed Airplane object
     * @param airplane Airplane *
     */
    void airplaneUpdateMaintenancePeriod(Airplane *airplane);

    /**
    * @brief Prints the tickets of the Passenger passed as argument, prints indexs if idx is set to true
    * @param passenger Passenger* passenger
    * @param idx bool idx
    */
    void showAllTickets(Passenger *passenger, bool idx);

    /**
    * @brief Prints the total information of a desired Flight of an Airplane
    * @param  airplane Airplane* airplane
    */
    void flightShow(Airplane *airplane);

    /**
    * @brief Creates a Flight and inserts it into the Airplane passed as argument
    * @param  airplane Airplane* airplane
    */
    void flightCreate(Airplane *airplane);

    /**
    * @brief Deletes a Flight
    * @param  airplane Airplane* airplane
    */
    void flightDelete(Airplane *airplane);

    /**
    * @brief Prints the summary of Flights in the Airplane
    * @param airplane Airplane* airplane
    */
    void printSummaryFlight(Airplane *airplane);

    /**
    * @brief Choses the id of the flight and returns it
    * @param airplane Airplane* airplane
    * @return Flight *
    */
    Flight *chooseFlight(Airplane *airplane);

    /**
    * @brief Validates a flight id passed as argument
    * @param id int id
    */
    void validFlight(int id);

    /**
     * @brief calls the function flightUpdatePrice
     */
    void flightUpdatePrice(Airplane *airplane);

    /**
    * @brief Updates the base price of the Flight passed as argument
    * @param flight Flight* flight
    */
    void flightUpdatePrice(Flight *flight);

    /**
    * @brief Adds the Passenger passed as argument to the Flight pointed by the argument passed
    * @param flight Flight* flight
    * @param passenger Passenger* passenger
    */
    void flightAddPassenger(Flight *flight, Passenger *passenger);

    /**
    * @brief Returns the seat chosen by the user on the Flight passed as argument
    * @param vector <string> seats
    * @return string
    */
    string chooseSeat(vector<string> seats);

    /**
    * @brief Returns the avaiable seats on the Flight passed as argument depending on the capacity passed as argument
    * @param flight Flight * flight
    * @param capacity unsigned int capacity
    * @return vector<string>
    */
    vector<string> availableSeats(Flight *flight, unsigned int capacity);

    /**
    * @brief Prints the seats on the screen to show the User a more graphic layout of the seats avaiable on the Flight
    * @param capacity unsigned int capacity
    * @param seats vector<string> seats
    */
    void printSeats(unsigned int capacity, vector<string> seats);

    /**
    * @brief Auxiliar function that manages the returning of a ticket
    * @param p Passenger *p
    */
    void returnTicket(Passenger *p);

    /**
    * @brief Gets the tickets of the Passenger passed as argument
    * @param Passenger *p
    * @return vector< pair<string, Flight*>>
    */
    vector<pair<string, Flight *> > getTickets(Passenger *p);

    /**
    * @brief Auxiliar function that manages the buying of a ticket
    * @param p Passenger *p
    */
    void bookFlight(Passenger *p);

    /**
    * @brief Auxiliar function that manages the buying of a ticket but already knows the type of ticket the user wants
    * @param p Passenger *p
    * @param type string type
    */
    void bookFlightWithType(Passenger *p, string type);

    /**
    * @brief Prints the Flights of the type passed as argument from the vector and the passenger passed
    * @param p Passenger *p
    * @param type string type
    * @param  fvector vector<Flight *> &fvector
    */
    void printFlightsByType(Passenger *p, string type, vector<Flight *> &fvector);

    /**
    * @brief Returns a Flight pointer of the Flight ID passed as argument
    * @param p Passenger *p
    * @param fvector vector<Flight*> &fvector
    * @return Flight *
    */
    Flight *chooseFlight(unsigned int id, vector<Flight *> &fvector);

    /**
    * @brief Calculates and returns the ticket price based on the Passenger, Flight and the type passed as argument
    * @param p Passenger *p
    * @param f Flight *f
    * @param type string type
    * @return float
    */
    float ticketPrice(Passenger *p, Flight *f, string type);

    /**
    * @brief Gets a vector of flights based on just the type of the Flight (commercial or rented) to let the user pick the one he wants afterwards
    * @param type string type
    * @return vector \< Flight * \>
    */
    vector<Flight *> getFlightsWithType(string type);

    /**
    * @brief Sorts the passengers by ID
    */
    void sortPassengers();

    /**
    * @brief Sorts the Flights by ID
    */
    void sortFlights();

    /**
    * @brief Calls the function passengerCreate()
    */
    void passengerCreateWrapper();

    /**
    * @brief Deletes the vector based on the argument
    * @param identifier string identifier
    */
    void clearData(string identifier);

    /**
    * @brief Calls the function showAllTicketsWrapper()
    * @param p Passenger *p
    */
    void showAllTicketsWrapper(Passenger *p);

    /**
    * @brief Adds the Passenger passed as argument to the passengers vector of the company
    * @param passenger Passenger *passenger
    */
    void addObject(Passenger *passenger);

    /**
    * @brief Adds the Flight passed as argument to the flight vector of the company
    * @param flight Flight *flight
    */
    void addObject(Flight *flight);

    /**
    * @brief Adds the Airplanes passed as argument to the airplane vector of the company
    * @param airplane Airplane *airplane
    */
    void addObject(Airplane *airplane);

    /**
     * @brief Removes form the vector flights the flight passed as argument
     * @param flight Flight * flight
     */
    void removeFlight(Flight *flight);

    /**
     * @brief Prints time restrictions to ensure connection flights
     * @param airplane
     */
    void printRestrictions(Airplane *airplane);

    /**
     * @brief Removes passenger from all flights
     * @param passenger Passenger * passenger
     */
    void removePassengerFromFlights(Passenger *passenger);

    /**
     * @brief Based on a model of an Airplane, goes to the priority queue and chooses a Technician * to be returned
     * @param model string model
     * @return Technician *
     */
    Technician *chooseTechnician(string model);

    /**
     * @brief Helper function to allow the user to choose a Technician
     * @return Technician *
     */
    Technician *chooseTechnician();

    /**
     * @brief Verifies if the passed argument id is a valid id of a Technician
     * @param id int id
     */
    void validTechnician(int id);

    /**
     * @brief Prints the next Maintenance sessions scheduled
     */
    void printNextMaintenanceSessions();

    /**
     * @brief Print the Maintenance sessions between two dates
     */
    void printMaintenancePeriod();


    void techRemovefromQueue(Technician *tech);

    /**
     * @brief Creates a new Technician and adds it to the Company priority queue technicians after validating the information
     */
    void technicianCreate();

    /**
    * @brief Prints the total information of a desired Technician
    */
    void technicianShow();

    /**
      * @brief Deletes the pretended Technician from the Company priority queue containing the technicians
      */
    void technicianDelete();

    /**
     * @brief Updates the name of the technician passed as argument (pointer) to the one inputed by the user
     * @param technician Technician* technician
     */
    void technicianUpdateName(Technician *technician);

    /**
     * @brief Adds a string model inputed by the user in the vector of strings models of the object Technician
     * @param technician  Technician* technician
     */
    void technicianAddModel(Technician *technician);

    /**
     * @brief Deletes a string model inputed by the user in the vector of strings models of the object Technician
     * @param technician  Technician* technician
     */
    void technicianDeleteModel(Technician *technician);

    /**
     * @brief Prints the summary of a Technician
     */
    void printSummaryTechnician() const;

    /**
     * @brief Pushes the passed argument in the priority queue technicians of the Company class
     * @param technician Technician* technician
     */
    void addObject(Technician *technician);

    /**
     * @brief Resets all the state flags (passengersChanged, techniciansChanged, airplanesChanged and flightsChanged) to the false state
     */
    void setFlag();

    /**
     * @brief Gets the id of the next Booking
     * @return id
     */
    unsigned int getNextBookingId();

    /**
     * @brief Adds the passed argument Booking * booking to the vector of Booking of the class Company
     * @param booking Booking * booking
     */
    void addBooking(Booking *booking);

    /**
     * @brief
     * @param flight Flight * flight
     */
    void addBookingsFromFlight(Flight *flight);

    /**
     * @brief Adds a Passenger * to the Hash Table of inactive passengers of the class Company
     * @param passenger Passenger* passenger
     */
    void addInactivePassenger(Passenger *passenger);

    /**
     * @brief Removes the desired Passenger passed as parameter from the inactivePassengers hash table
     * @param passenger Passenger * passenger
     */
    void removeInactivePassenger(Passenger *passenger);

    /**
     * @brief Checks if a flights Date has already passed
     * @param f Flight * f
     * @return true if it's in the past or false otherwise(future)
     */
    bool pastFlight(Flight *f);

    /**
     * @brief Checks if a passenger passed as argument is inactive or not
     * @param p Passenger * p
     * @return true if the Passenger * p is inactive and false otherwise
     */
    bool inactivePassenger(Passenger *p);

    /**
     * @brief Gets the last reservation of a passed Passenger pointer to help with inactivity functions
     * @param p Passenger * p
     * @return Date
     */
    Date getLastReservation(Passenger *p);

    /**
     *  @brief Update the Time of the program
     */
    void updateTime();

    /**
     * @brief Updates the bookings according to the time
     */
    void updateBookings();

    /**
     * @brief Updates the flights according to the time
     */
    void updateFlights();

    /**
     * @brief Updates the passengers according to the time
     */
    void updatePassengers();

    /**
     * @brief Gets all the passengers that are registered in the system
     * @return vector <Passenger*>
     */
    vector<Passenger *> getAllPassengers();

    /**
     * @brief Removes the passenger passed as argument from the bookings vector
     * @param passenger Passenger * passenger
     */
    void removePassengerFromBookings(Passenger *passenger);

    /**
     * @brief Gets all the inactive Passengers
     * @return vector<Passenger *>
     */
    vector<Passenger *> getIncPassengers();

    /**
     * @brief Updates the Date on the Airplanes
     */
    void updateAirplanesDate();

    /**
     * @brief Updates the Date on the technicians
     */
    void updateTechniciansDate();

};

#endif //AEDA_FEUP_PROJECT_COMPANY_H
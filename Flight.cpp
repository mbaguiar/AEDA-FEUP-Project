#include "Flight.h"

Flight::Flight(unsigned int id, string departure, string destination, unsigned int time_to_flight, unsigned int basePrice, unsigned int duration): id(id), departure(departure),
                destination(destination), time_to_flight(time_to_flight), basePrice(basePrice), duration(duration) {}

string Flight::getDeparture() const
{
    return this->departure;
}

string Flight::getDestination() const
{
    return this->destination;
}

unsigned int Flight::getTime_to_flight() const
{
    return this->time_to_flight;
}

unsigned int Flight::getBasePrice() const
{
    return this->basePrice;
}

unsigned int Flight::getDuration() const
{
    return this->duration;
}

void Flight::setDeparture(string departure)
{
    this->departure = departure;
}

void Flight::setDestination(string destination)
{
    this->destination = destination;
}

void Flight::setTime_to_flight(unsigned int time_to_flight)
{
    this->time_to_flight = time_to_flight;
}

void Flight::setBasePrice(unsigned int basePrice)
{
    this->basePrice = basePrice;
}

void Flight::setDuration(unsigned int duration)
{
    this->duration = duration;
}

void Flight::printSummary() {

    cout << "Departure: " << departure;
    cout << "Destination: " << destination;
    cout << "Time to flight: " << time_to_flight << endl;

}

void Flight::print() {

    cout << "Departure: " << departure << endl;
    cout << "Destination: " << destination << endl;
    cout << "Time to flight: " << time_to_flight << endl;
    cout << "Base Price: " << basePrice << endl;
    cout << "Flight duration: " << duration << endl;
}

unsigned int Flight::getId() {
    return this->id;
}

RentedFlight::RentedFlight(unsigned int id, string departure, string destination, unsigned int time_to_flight, unsigned int basePrice, unsigned int duration, Passenger *buyer) : Flight(id, departure, destination, time_to_flight, basePrice, duration), buyer(buyer) {}

Passenger * RentedFlight::getBuyer() const {

    return this-> buyer;
}

void RentedFlight::setBuyer(Passenger *buyer) {

    this->buyer = buyer;
}

void RentedFlight::print() {

    Flight::print();
    cout << "Buyer: ";
    buyer->printSummary();
    cout << endl;
}

ComercialFlight::ComercialFlight(unsigned int id, string departure, string destination, unsigned int time_to_flight, unsigned int basePrice, unsigned int duration, map<string, Passenger *> passengers) : Flight(id, departure, destination, time_to_flight, basePrice, duration), passengers(passengers) {}


PassengerMap ComercialFlight::getPassengers() const {

    return this->passengers;
}

void ComercialFlight::setPassengers(PassengerMap passengers) {

    this->passengers = passengers;
}

void ComercialFlight::print() {

    cout << "Passengers:\n";

    Flight::print();

    for (auto& p : passengers) {

        Passenger* passenger = p.second;

        passenger->printSummary();
    }

}
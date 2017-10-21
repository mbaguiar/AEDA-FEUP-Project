#include "Flight.h"

Flight::Flight(string departure, string destination, int time_to_flight, int basePrice, int duration)
{
}

string Flight::getDeparture() const
{
	return this->departure;
}

string Flight::getDestination() const
{
	return this->destination;
}

int Flight::getTime_to_flight() const
{
	return this->time_to_flight;
}

int Flight::getBasePrice() const
{
	return this->basePrice;
}

int Flight::getDuration() const
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

void Flight::setTime_to_flight(int time_to_flight)
{
    this->time_to_flight = time_to_flight;
}

void Flight::setBasePrice(int basePrice)
{
    this->basePrice = basePrice;
}

void Flight::setDuration(int duration)
{
    this->duration = duration;
}

RentedFlight::RentedFlight(string departure1, string destination1, int time_to_flight1, int basePrice1,
                           int duration1, string departure, string destination, int time_to_flight, int basePrice,
                           int duration, Passenger *buyer) : Flight(departure1, destination1, time_to_flight1, basePrice1, duration1), buyer(buyer) {}

Passenger * RentedFlight::getBuyer() const {

    return this-> buyer;
}

void RentedFlight::setBuyer(Passenger *buyer) {

    this->buyer = buyer;
}

ComercialFlight::ComercialFlight(string departure1, string destination1, int time_to_flight1, int basePrice1,
                                 int duration1, string departure, string destination, int time_to_flight,
                                 int basePrice, int duration, vector<Passenger *> passengers) : Flight(departure1, destination1, time_to_flight1, basePrice1, duration1), passengers(passengers) {}

vector<Passenger *> ComercialFlight::getPassengers() const {

    return this->passengers;
}

void ComercialFlight::setPassengers(vector<Passenger *> passengers) {

    this->passengers = passengers;
}
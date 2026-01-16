//
//  ECFlight.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlight.h"
#include "ECAirport.h"

#include <iostream>
using namespace std;

ECFlight :: ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn) 
    : srcAirport(srcIn), destAirport(destIn), departureTime(tmDepartIn), maxPassengers(maxPassengersIn){
    CalculateArrivalTime();
}

void ECFlight :: CalculateArrivalTime() {
    ECAirportInfo* airportInfo = ECAirportInfo::GetInstance();
    double flightTime = airportInfo->CalculateFlightTime(GetSource(), GetDest());
    arrivalTime = GetDepartureTime() + flightTime;
}



//
//  ECAirport.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECAirport.h"
#include <map> 

#include <iostream>

/**********************************************/
// ECAirport Implementation
ECAirport :: ECAirport() {}

ECAirport :: ECAirport(const std::string &nameAP, const std::string &codeIATA) : name(nameAP), codeIATA(codeIATA) {}

ECAirport :: ECAirport (const ECAirport &rhs) {} 


/**********************************************/
//ECAirportInfo
ECAirportInfo* ECAirportInfo::instance = nullptr;

ECAirportInfo :: ECAirportInfo() {}

void ECAirportInfo :: CreateAirport(const std::string &name, const std::string &code) {
    ECAirport airport(name, code);
    airports[code] = airport;
}

const ECAirport& ECAirportInfo :: GetAirport(const std::string &code) const{   
    if (airports.find(code) == airports.end()){
        throw std::string("Airport not found");
    }
    return airports.at(code);
}
//Set the distances in a map between the two airports
void ECAirportInfo :: SetDistance(const std::string &ap1Code, const std::string &ap2Code, int dist){ 
    AirportDist[std::pair<std::string, std::string>(ap1Code, ap2Code)] = dist;
    AirportDist[std::pair<std::string, std::string>(ap2Code, ap1Code)] = dist;
}

//Returns the distances between the two airports
int ECAirportInfo :: GetDistance(const std::string &ap1Code, const std::string &ap2Code) const{
    return AirportDist.at(std::pair<std::string, std::string>(ap1Code, ap2Code));
}

void ECAirportInfo :: FindFlightTime(const std::string &ap1Code, const std::string &ap2Code, int dist){
    AirportTimetoTime[std::pair<std::string, std::string>(ap1Code, ap2Code)] = dist/500.0;
    AirportTimetoTime[std::pair<std::string, std::string>(ap2Code, ap1Code)] = dist/500.0;
}

double ECAirportInfo :: CalculateFlightTime(const std::string &ap1Code, const std::string &ap2Code) const{
    return AirportTimetoTime.at(std::pair<std::string, std::string>(ap1Code, ap2Code));
}

ECAirportInfo* ECAirportInfo :: GetInstance(){
    if (instance == nullptr){
        instance = new ECAirportInfo();
    }
    return instance;
}


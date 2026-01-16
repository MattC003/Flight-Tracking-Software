//
//  ECAirlineSimulator.hpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//  Simulate airline activities: booking, flights, etc

#ifndef ECAirlineSimulator_h
#define ECAirlineSimulator_h

#include <string>
#include <set>

class ECAirlineOperation;
class ECAirlineTicketing;
class ECAirlineFinancial;
class ECFlightItinerary;
class ECFlight;

//****************************************************************************
// Airline simulator

class ECAirlineSimulator
{
public:
    ECAirlineSimulator() {Init();};
    virtual ~ECAirlineSimulator() {delete pAirlineOp;};
    
    // *****************************************************
    // Configuration
    
    // Adding airport with name and IATA code
    void AddAirport(const std::string &name, const std::string &code);
    
    // Setup distaince between airport; note distance is symmetric: the distance from dest to src is the same as from src to dest
    void SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist);
    
    // Adding flights: src airport, dest airport, depart time, max number of passenger, operating cost
    void AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate );
    
    // Called to indicate no more flights to add
    void DoneFlightAdding(){};
    

    // *****************************************************
    // Flight search

    void SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) const;
    
    //depth first search to find all possible itineraries
    void Search(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const;

    ECAirlineOperation *GetAirlineOp() { return pAirlineOp; }

    // Returns for now 
    void PreferLowPrice() {return;}
    void PreferShortTime() {return;}
    void PreferEarlyArrival() {return;}
    
    
private:
    // initialize
    void Init();
    
    // key data member
    ECAirlineOperation *pAirlineOp;
};

#endif /* ECAirlineSimulator_h */
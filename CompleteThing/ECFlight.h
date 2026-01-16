//
//  ECFlight.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlight_h
#define ECFlight_h

#include <string>


// ****************************************************************************
// Flight: service between two airports at a specific time;

class ECFlight 
{
public:
    ECFlight(const std::string &srcIn, const std::string &destIn, double tmDepartIn, int maxPassengersIn);

    virtual ~ECFlight(){}
    
    // Get departure time
    double GetDepartureTime() const {return departureTime;};
    
    // Get arrival time
    double GetArrivalTime() const {return arrivalTime;};
    
    // Set max passenger for this flight
    void SetMaxNumPassengers(int m) {maxPassengers = m;}
    
    // Get src airport code
    std::string GetSource() const {return srcAirport;}
    
    // Get destination code
    std::string GetDest() const {return destAirport;};

    // more to add...  

    int GetMaxNumPassengers() const {return maxPassengers;};

    void CalculateArrivalTime();

    double arrivalTime; 

private:
    // your code
    std::string srcAirport;
    std::string destAirport;
    double maxPassengers;
    double departureTime;
};

#endif /* ECFlight_h */

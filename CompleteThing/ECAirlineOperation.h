//
//  ECAirlineOperation.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//  About operation of an airline: especially flights management

#ifndef ECAirlineOperation_h
#define ECAirlineOperation_h

#include <vector>
#include "ECFlight.h"

class ECAirlineOperation
{
public:
    ECAirlineOperation() {}
    ~ECAirlineOperation() {}

    void addFlight(ECFlight* flight);
    std::vector<ECFlight *> GetFlights() { return listFlights; }

private:
    std::vector<ECFlight *> listFlights; 
};

#endif
//
//  ECAirlineSimulator.cpp
//  
//
//  Created by Yufeng Wu on 5/17/23.
//

#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECAirport.h"
#include "ECFlight.h"
#include "ECFlightItinerary.h"

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

void ECAirlineSimulator :: AddAirport(const std::string &name, const std::string &code)
{
    ECAirport *pECAirport = new ECAirport(name, code);
    ECAirportInfo::GetInstance()->CreateAirport(name, code);
}

void ECAirlineSimulator :: SetDistBtwAirports(const std::string &srcAirport, const std::string &destAirport, int dist)
{
    ECAirportInfo::GetInstance()->SetDistance(srcAirport, destAirport, dist);
    ECAirportInfo::GetInstance()->FindFlightTime(srcAirport, destAirport, dist);
}

void ECAirlineSimulator :: AddFlight(const std::string &srcAirport, const std::string &destAirport, double tmDepart, int maxPassengers, double costOperate )
{
    ECFlight *pFlight = new ECFlight(srcAirport, destAirport, tmDepart, maxPassengers);
    pAirlineOp->addFlight(pFlight);
}



void ECAirlineSimulator::Search(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries) const
{
    std::vector<ECFlight *> currFlights = pAirlineOp->GetFlights();
    std::map<std::string, std::vector<ECFlight *>> adj;

    for (auto flight : currFlights)
    {
        adj[flight->GetSource()].push_back(flight);
    }

    std::stack<ECFlightItinerary> s;

    for (auto flight : adj[src])
    {
        ECFlightItinerary itinerary;
        itinerary.AddSegment(flight);
        s.push(itinerary);
    }

    while (!s.empty())
    {
        ECFlightItinerary currentItinerary = s.top();
        s.pop();

        ECFlight *lastFlight = currentItinerary.GetSegment(currentItinerary.GetNumSegments() - 1);

        if (lastFlight->GetDest() == dest)
        {
            listItineraries.push_back(currentItinerary);
        }

        std::set<std::string> visited;

        for (int i = 0; i < currentItinerary.GetNumSegments(); i++)
        {
            visited.insert(currentItinerary.GetSegment(i)->GetSource());
        }

        for (auto flight : adj[lastFlight->GetDest()])
        {
            if (flight->GetDepartureTime() >= lastFlight->GetArrivalTime() &&
                visited.find(flight->GetDest()) == visited.end())
            {
                ECFlightItinerary newItinerary = currentItinerary;
                newItinerary.AddSegment(flight);
                s.push(newItinerary);
            }
        }
    }
}

void ECAirlineSimulator :: SearchForFlights(const std::string &src, const std::string &dest, std::vector<ECFlightItinerary> &listItineraries ) const
{
    if (src != dest)
    {
        Search(src, dest, listItineraries);
    }
    return;
}

/********************INITIALIZATION******************/
void ECAirlineSimulator :: Init()
{
    pAirlineOp = new ECAirlineOperation;
}
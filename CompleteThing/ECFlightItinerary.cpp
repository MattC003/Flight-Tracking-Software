//
//  ECFlightItinerary.cpp
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#include "ECFlightItinerary.h"
#include "ECFlight.h"
#include <iostream>
#include <string>
#include <set>
using namespace std;


double ECFlightItinerary :: GetFlightTime() const
{
    double totalTime;
    int i = 0;

    while (i < segments.size())
    {
        totalTime += segments[i]->GetArrivalTime() - segments[i]->GetDepartureTime();
        i++;
    }

    return totalTime;
}

double ECFlightItinerary :: GetTimeAllSegments() const
{
    int size = segments.size();
    return segments[size - 1]->GetArrivalTime() - segments[0]->GetDepartureTime();
}

double ECFlightItinerary :: GetDepartTime() const
{
    return segments[0]->GetDepartureTime(); 
}

double ECFlightItinerary :: GetArrivalTime() const
{
    int size = segments.size();
    return segments[size - 1]->GetArrivalTime();

}

double ECFlightItinerary :: GetPrice() const
{
    return GetFlightTime() * 120;
}

//prints out the whole itinerary
void ECFlightItinerary :: Dump() const
{
    int i = 0;
    cout << "Itinerary: \n";
    do{
        cout << segments[i]->GetSource() << " -> " << segments[i]->GetDest() << " , ";
        cout << "Depart time: " << segments[i]->GetDepartureTime() << " " << segments[i]->GetArrivalTime() << " " << endl;
        i++;
    } while (i < segments.size());
    cout << endl;
}
//
//  ECFlightItinerary.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECFlightItinerary_h
#define ECFlightItinerary_h

#include <vector>
#include <string>

class ECFlight;
class ECAirlineFinancial;

// ****************************************************************************
// Flight itineary: consisting segments of flights so to go from one airport to another airport

class ECFlightItinerary
{
public:
    ECFlightItinerary(){};
    ~ECFlightItinerary(){segments.clear();};

    // access/edit segments
    // Return the number of segments of the itineary
    int GetNumSegments() const{ return segments.size();};
    
    // Return a segment
    ECFlight *GetSegment(int segIndex) const { return segments[segIndex];};
    
    // Get flight time: from departure to arrival
    double GetFlightTime() const;
    
    // Get segment time: add the time of all segments
    double GetTimeAllSegments() const;
    
    // Get departure time
    double GetDepartTime() const;
    
    // Get arrival time
    double GetArrivalTime() const;
    
    // Price 
    double GetPrice() const;

    void AddSegment(ECFlight *seg) {segments.push_back(seg);};

    void Dump() const; 
    
private:
    // your code
    std::vector<ECFlight *> segments;
};

#endif /* ECFlightItinerary_h */
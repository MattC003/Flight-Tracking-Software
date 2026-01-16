//
//  ECAirport.h
//  
//
//  Created by Yufeng Wu on 5/11/23.
//

#ifndef ECAirport_h
#define ECAirport_h

#include <string>
#include <set>
#include <map>


// ****************************************************************************
// Airport: start/end point of a flight

class ECAirport 
{
public:
    // by default, airport is operating (except in default constructor)
    ECAirport(); 
    ECAirport(const std::string &nameAP, const std::string &codeIATA);
    ECAirport(const ECAirport &rhs);
    
    // Get the name of the airport
    std::string GetName() const {return name;};
    
    // Get IATA code
    std::string GetCode() const {return codeIATA;}
    
    // Operating status: is it operating normally?
    bool IsOperating() const {return operating;}
    
    // Set operating status
    void SetOperating(bool f) {operating = f;}
    
private:
    // your ocde
    std::string name;
    std::string codeIATA; 
    bool operating;
};

// ****************************************************************************
// Airport info: access airport information
// Use singleton pattern

class ECAirportInfo
{
public:
    
    // Create a new airport in the system
    void CreateAirport(const std::string &name, const std::string &code);
    
    // Get airport by code
    // Throw exception (std::string) if there is no airport with the code
    const ECAirport &GetAirport(const std::string &code) const;
    
    // Set distance (in miles) between airports
    void SetDistance(const std::string &ap1Code, const std::string &ap2Code, int dist);
    
    // more to add...
    int GetDistance(const std::string &ap1Code, const std::string &ap2Code) const;

    void FindFlightTime(const std::string &ap1Code, const std::string &ap2Code, int dist);

    double CalculateFlightTime(const std::string &ap1Code, const std::string &ap2Code) const;

    static ECAirportInfo *GetInstance();

    std::map<std::string, ECAirport> GetAirports() const {return airports;};

    ECAirportInfo();
    
private:
   // your code 
    static ECAirportInfo* instance;
    double time; 
    std::map<std::string, ECAirport> airports;
    std::map<std::pair<std::string, std::string>, int> AirportDist;
    std::map<std::pair<std::string, std::string>, double> AirportTimetoTime; 
};


#endif /* ECAirport_h */
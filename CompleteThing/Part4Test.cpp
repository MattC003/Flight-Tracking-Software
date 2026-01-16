#include "ECAirport.h"
#include "ECFlight.h"
#include "ECConsoleUIListBox.h"
#include "ECConsoleUIButton.h"
#include "ECConsoleUITextField.h"
#include "ECAirlineSimulator.h"
#include "ECAirlineOperation.h"
#include "ECAirlineTicketing.h"
#include "ECAirlineFinancial.h"
#include "ECFlightItinerary.h"
using namespace std;

#include <iostream>
#include <fstream>
#include <sstream>

void LoadDataFromFile(const std::string& filename, ECAirlineSimulator& sim) {
    std::ifstream file(filename);
    std::string line;
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip comments and empty lines

        std::istringstream iss(line);
        int type;
        iss >> type;

        if (type == 1) { // Airport information
            std::string code, name;
            iss >> code;
            getline(iss, name);
            name = name.substr(1); // Remove leading space
            sim.AddAirport(name, code);
        } else if (type == 2) { // Distance information
            std::string origin, dest;
            int distance;
            iss >> origin >> dest >> distance;
            sim.SetDistBtwAirports(origin, dest, distance);
        } else if (type == 3) { // Flight information
            std::string origin, dest;
            double time;
            int length, cost;
            iss >> origin >> dest >> time >> length >> cost;
            sim.AddFlight(origin, dest, time, length, cost);
        }
    }

    file.close();
}

class CustomButton : public ECConsoleUIButton {
public:
    CustomButton(int x1, int y1, int x2, int y2, const std::string& label, ECAirlineSimulator* sim, ECConsoleUIListBox* srcBox, ECConsoleUIListBox* destBox, ECConsoleUIListBox* itineraryListBox)
        : ECConsoleUIButton(x1 , y1 + 2, x2, y2, label), sim(sim), srcBox(srcBox), destBox(destBox), itineraryListBox(itineraryListBox) {}

    virtual void HdlKeyEnter() override {
        
        // Retrieve the selected source and destination airports
        itineraryListBox-> choices.clear();
        std::string src = srcBox->choices[srcBox->GetChoice()];
        std::string dest = destBox->choices[destBox->GetChoice()];

        // Fetch flight itineraries between source and destination airports
        std::vector<ECFlightItinerary> itineraries;
        sim->SearchForFlights(src, dest, itineraries);
        
        // Add flight itineraries to the list box
        for (const auto& itinerary : itineraries) {
            itineraryListBox->AddChoice(src + " > " + dest);
            itineraryListBox->AddChoice("Departure Time: " + std::to_string(itinerary.GetDepartTime()));
            itineraryListBox->AddChoice("Cost: " + std::to_string(itinerary.GetPrice()) + ", Flight Time: " + std::to_string(itinerary.GetFlightTime()));

        }
    }

private:
    ECAirlineSimulator* sim;
    ECConsoleUIListBox* srcBox;
    ECConsoleUIListBox* destBox;
    ECConsoleUIListBox* itineraryListBox;
};

void Test1(ECConsoleUIView &viewTest, ECAirlineSimulator &sim, ECConsoleUIListBox &srcBox, ECConsoleUIListBox &destBox) {
    // Create a highlighted text label and borders
    ECConsoleUITextLabel *pl1 = new ECConsoleUITextLabel(30, 1, "3150 Matt Final Project");
    pl1->SetHighlight(true);
    viewTest.AddUIItem(pl1);
    string horizBar;
    for(int i=0; i<viewTest.GetColNumInView(); ++i) { horizBar += '-'; }
    viewTest.AddUIItem(new ECConsoleUITextLabel(0, 0, horizBar));
    viewTest.AddUIItem(new ECConsoleUITextLabel(0, viewTest.GetRowNumInView()-1, horizBar));

    // Vector to store loaded airports
    std::vector<std::string> loadedAirports;

    // Load airport data from file
    std::ifstream file("airports.txt");
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip comments and empty lines
        std::istringstream iss(line);
        int type;
        iss >> type;
        if (type == 1) { // Airport information
            std::string code, name;
            iss >> code;
            std::getline(iss, name);
            name = name.substr(1); // Remove leading space
            loadedAirports.emplace_back(code);
        }
    }
    file.close();

    // Prepare list boxes for Sources and Destinations
    ECConsoleUIListBox *px2 = new ECConsoleUIListBox(15, 15, 30, 17);
    ECConsoleUIListBox *px3 = new ECConsoleUIListBox(40, 15, 55, 17);

    // Populate the list boxes using the loaded airports
    for (const auto& code : loadedAirports) {
        px2->AddChoice(code);
        px3->AddChoice(code);
    }

    viewTest.AddUIItem(new ECConsoleUITextLabel(15, 12, "Sources"));
    viewTest.AddUIItem(px2);
    viewTest.AddUIItem(new ECConsoleUITextLabel(40, 12, "Destinations"));
    viewTest.AddUIItem(px3);

    // Add Itinerary display list box after the button
    ECConsoleUIListBox *itineraryListBox = new ECConsoleUIListBox(15, 25, 55, 32);
    viewTest.AddUIItem(new ECConsoleUITextLabel(15, 24, "Itineraries"));
    viewTest.AddUIItem(itineraryListBox);

    // Add a UI button beneath the lists with some space in between
    CustomButton *btn = new CustomButton(15, 20, 30, 22, "Find flight", &sim, px2, px3, itineraryListBox);
    viewTest.AddUIItem(btn);



    // Refresh the view
    viewTest.Refresh();
}





int main() {
    ECAirlineSimulator sim;
    LoadDataFromFile("txtfile.txt", sim);
    ECTextViewImp wndTest;
    ECConsoleUIView viewUI(&wndTest);
    ECConsoleUIListBox srcBox(15, 15, 30, 17);
    ECConsoleUIListBox destBox(40, 15, 55, 17);

    Test1(viewUI, sim, srcBox, destBox);
    viewUI.Refresh();
    try {
        wndTest.Show();
    } catch(const std::string& ex) {
        std::cout << "Exception: " << ex << std::endl;
    }
    return 0;
}
//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"

#include <algorithm>
#include <string>

using namespace std;

// Constructor implementation
ECConsoleUIListBox::ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR) : ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0) {}

// Add choice item to the list
void ECConsoleUIListBox::AddChoice(const string &text) {
    choices.push_back(text);
}

// choose an item based on if the index is within the range of the choices
void ECConsoleUIListBox::Choose(int rIndex) {
    if (rIndex >= 0 && rIndex < choices.size()) {
        indexChoice = rIndex;
    }
}

// Find the length of the string and highlight it all
// The first line will always be highlighted
int ECConsoleUIListBox :: GetHighlightPosition(int &xLeft, int &xRight) const {
    xLeft = 0;
    xRight = GetWidth();
    return 0;
}


std::string ECConsoleUIListBox::GetTextAtRow(int r) const {
    //initialize an empty string
    std::string StringReturn;

    //The offset from the top left corner of the list box
    int Offset = r - GetYUL();

    //returns an empty string if the offset is out of bounds
    if(Offset + indexChoice >= choices.size() || Offset < 0 || Offset >= GetHeight() || Offset >= choices.size()) {
        return StringReturn;
    }

    //returns the string at the index of the choice
    StringReturn = choices[indexChoice + Offset];
    StringReturn.resize(GetWidth());
    return StringReturn;
    }

bool ECConsoleUIListBox :: IsHandlingKeys() const{
    return true;
}

//moves toward the top, if already stay at the same position
void ECConsoleUIListBox :: HdlKeyUp() {
    if(indexChoice == 0) {
        Choose(indexChoice);
    }   else {
        Choose(indexChoice - 1);
    }
}

//moves toward the bottom, if already stay at the same position
void ECConsoleUIListBox :: HdlKeyDown() {
    if(indexChoice == choices.size() - 1){
        Choose(indexChoice);
    }   else {
        Choose(indexChoice + 1);
    }
}



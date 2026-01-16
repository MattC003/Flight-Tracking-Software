//
//  ECConsoleUITextField.cpp
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#include "ECConsoleUITextField.h"
#include "ECTextViewImp.h"

using namespace std;

ECConsoleUITextField :: ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len) : ECConsoleUIItem(xpos, ypos, xpos + len - 1, ypos), pTextView(pTextView), text(""), edit(false), maxL(len-1){}

//Starts at the : on the left then highlights to the length of the text when on the text field
int ECConsoleUITextField::GetHighlightPosition(int &xLeft, int &xRight) const {
    if (edit) {
        xLeft = 1; 
        xRight = 1 + text.length();
        return GetYUL();
    }
    return -1;
}

//returns true if the text field is handling keys
bool ECConsoleUITextField :: IsHandlingKeys() const{
    return true;
}

//starts the field with a colon and the text otherwise it returns an empty string
std::string ECConsoleUITextField::GetTextAtRow(int r) const {
    std::string empty;
    if (r == GetYUL()) {
        return ':' + text; 
        }
    return empty;
    }

//moves the cursor to the end of the text field and enables editing on the text field
void ECConsoleUITextField :: HdlKeyEnter() {
    edit = true;
    pTextView->SetCursorX(GetXUL() + text.length() + 1);

}

void ECConsoleUITextField::HdlOtherKey() {
    int key = pTextView->GetPressedKey(); // Track the key pressed
    if (!edit) return; // Early return if not in editing mode

    // Update cursor positions
    int cursorX = pTextView->GetCursorX() - GetXUL(); 
    int cursorY = pTextView->GetCursorY() - GetYUL(); // Unused, but potentially useful for multi-line support

    switch (key) {
        case 127: // Backspace key
            handleBackspace(cursorX);
            break;
        case 3: // Ctrl+C
            edit = false; // Exit edit mode
            break;
        default:
            handleTyping(key, cursorX);
            break;
    }
}

void ECConsoleUITextField::handleBackspace(int &cursorX) {
    if (!text.empty()) {
        text.pop_back(); // Delete the last character
        cursorX = std::max(0, cursorX - 1); // Decrement cursor safely
        pTextView->SetCursorX(GetXUL() + cursorX);
    }
}

void ECConsoleUITextField::handleTyping(int key, int &cursorX) {
    if (text.size() < maxL) {
        text.push_back(static_cast<char>(key)); // Converts int to character and appends it
        cursorX++; // Increment cursor position
        pTextView->SetCursorX(GetXUL() + cursorX);
    }
}
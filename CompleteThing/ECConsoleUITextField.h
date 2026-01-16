//
//  ECConsoleUITextField.h
//  
//
//  Created by Yufeng Wu on 5/24/23.
//

#ifndef ECConsoleUITextField_h
#define ECConsoleUITextField_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"
class ECTextViewImp;

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUITextField : public ECConsoleUIItem
{
public:
    // specifiy the starting point of the text field
    ECConsoleUITextField(ECTextViewImp *pTextView, int xpos, int ypos, int len);
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const override;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const override;
    
    // Are there any other function you might need to override?
    virtual bool IsHandlingKeys() const override;

    virtual void HdlKeyEnter();

    virtual void HdlOtherKey() override;
    
    void SetCursorX(int x){};
    int GetCursorX() const{};

    void handleBackspace(int &cursorX);
    void handleTyping(int key, int &cursorX);

private:
    std::string text;
    ECTextViewImp* pTextView;
    bool edit;
    int maxL;
};

#endif /* ECConsoleUITextField_h */

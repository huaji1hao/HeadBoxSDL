#pragma once
#include "BaseEngine.h"
#include "DisplayableObject.h"

class TextInputField : public DisplayableObject {
public:
    TextInputField(int x, int y, int width, int height, BaseEngine* pEngine, Font* font)
        : DisplayableObject(x, y, pEngine, width, height, true),
        text(""), cursorPosition(0), isActive(false), pFont(font) {
        setVisible(true);
    }

    int getTextWidth(const std::string& str);

    // Handle key release events to capture text input
    void virtKeyUp(int iKeyCode) override;

    // Draw the text input field
    void virtDraw() override;

    // Mouse click event to activate the text field
    void virtMouseDown(int iButton, int iX, int iY) override;

    // Deactivate text field when clicking elsewhere
    void virtMouseUp(int iButton, int iX, int iY) override;

    // Get the text from the input field
    std::string getText() const;

protected:
    std::string text;            // Text content of the input field
    int cursorPosition;          // Position of the cursor in the text
    const size_t maxTextLength = 16; // Max text length for simplicity
    bool isActive;               // Whether this text field is currently active
    Font* pFont;                 // Font used for text rendering
};


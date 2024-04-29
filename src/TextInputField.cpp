#include "header.h"
#include "TextInputField.h"

TextInputField::TextInputField(int x, int y, int width, int height, BaseEngine* pEngine, Font* font)
    : DisplayableObject(x, y, pEngine, width, height, true),
    m_sText(""), cursorPosition(0), isActive(false), pFont(font) {
    setVisible(true);
}

void TextInputField::virtMouseDown(int iButton, int iX, int iY) {
    // Activate the text field if clicked
    isActive = virtIsPositionWithinObject(iX, iY);
}


void TextInputField::virtMouseUp(int iButton, int iX, int iY) {
    if (!virtIsPositionWithinObject(iX, iY)) {
        isActive = false;
    }
}


std::string TextInputField::getText() const {
    if (m_sText.empty())
        return "    <Enter Name>";
    return m_sText;
}


int TextInputField::getTextWidth(const std::string& str) {
    int w = 0, h = 0;
    if (pFont && pFont->getTTFFont()) {
        TTF_SizeText(pFont->getTTFFont(), str.c_str(), &w, &h);
    }
    return w;
}

void TextInputField::virtKeyUp(int iKeyCode) {
    if (!isActive) return;

    // Get the current keyboard state for shift key status
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    bool shiftPressed = keystate[SDL_SCANCODE_LSHIFT] || keystate[SDL_SCANCODE_RSHIFT];

    // Initialize character to add as null
    char charToAdd = '\0';

    // Handle alphanumeric and basic punctuation
    if ((iKeyCode >= SDLK_a && iKeyCode <= SDLK_z) || (iKeyCode >= SDLK_0 && iKeyCode <= SDLK_9) || iKeyCode == SDLK_SPACE) {
        if (iKeyCode >= SDLK_a && iKeyCode <= SDLK_z) {
            charToAdd = shiftPressed ? static_cast<char>(iKeyCode - SDLK_a + 'A') : static_cast<char>(iKeyCode);
        }
        else if (iKeyCode >= SDLK_0 && iKeyCode <= SDLK_9) {
            const char* numSymbols = ")!@#$%^&*(";
            charToAdd = shiftPressed ? numSymbols[iKeyCode - SDLK_0] : static_cast<char>(iKeyCode);
        }
        else if (iKeyCode == SDLK_SPACE) {
            charToAdd = ' ';
        }
    }
    else {
        // Handle other keys using a switch case for specific symbols
        switch (iKeyCode) {
        case SDLK_MINUS: charToAdd = shiftPressed ? '_' : '-'; break;
        case SDLK_EQUALS: charToAdd = shiftPressed ? '+' : '='; break;
        case SDLK_LEFTBRACKET: charToAdd = shiftPressed ? '{' : '['; break;
        case SDLK_RIGHTBRACKET: charToAdd = shiftPressed ? '}' : ']'; break;
        case SDLK_BACKSLASH: charToAdd = shiftPressed ? '|' : '\\'; break;
        case SDLK_SEMICOLON: charToAdd = shiftPressed ? ':' : ';'; break;
        case SDLK_QUOTE: charToAdd = shiftPressed ? '"' : '\''; break;
        case SDLK_COMMA: charToAdd = shiftPressed ? '<' : ','; break;
        case SDLK_PERIOD: charToAdd = shiftPressed ? '>' : '.'; break;
        case SDLK_SLASH: charToAdd = shiftPressed ? '?' : '/'; break;
        default: break;
        }
    }

    // Insert the character if it's not null and within the max text length
    if (charToAdd != '\0' && m_sText.length() < maxTextLength) {
        m_sText.insert(m_sText.begin() + cursorPosition, charToAdd);
        cursorPosition++;
    }

    // Handle backspace for deletion
    if (iKeyCode == SDLK_BACKSPACE && cursorPosition > 0) {
        m_sText.erase(m_sText.begin() + cursorPosition - 1);
        cursorPosition--;
    }

    // Handle left and right arrows for cursor movement
    if (iKeyCode == SDLK_LEFT && cursorPosition > 0) {
        cursorPosition--;
    }
    if (iKeyCode == SDLK_RIGHT && cursorPosition < m_sText.length()) {
        cursorPosition++;
    }

    // Optionally handle the enter key to deactivate input
    if (iKeyCode == SDLK_RETURN) {
        isActive = !isActive;
    }

    // Redraw the display after input changes
    getEngine()->redrawDisplay();
}

void TextInputField::virtDraw() {
    if (!isVisible())
        return;

    // Draw the background
    getEngine()->drawForegroundRectangle(m_iCurrentScreenX, m_iCurrentScreenY, m_iCurrentScreenX + m_iDrawWidth - 1, m_iCurrentScreenY + m_iDrawHeight - 1, 0xe9ecf2);

    // Draw the text
    getEngine()->drawForegroundString(m_iCurrentScreenX + 5, m_iCurrentScreenY + 5, getText().c_str(), 0x000000, pFont);

    // Optionally, draw the cursor
    if (isActive) {
        int cursorX = m_iCurrentScreenX + 5 + getTextWidth(m_sText.substr(0, cursorPosition));
        getEngine()->drawForegroundRectangle(cursorX, m_iCurrentScreenY + 5, cursorX, m_iCurrentScreenY + m_iDrawHeight - 10, 0x000000);
    }
}


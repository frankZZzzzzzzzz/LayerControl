#ifndef KEYBOARD_FUNCTIONALITY
#define KEYBOARD_FUNCTIONALITY

class KeyboardFunctionality{
public:
    virtual void keyPress(char key) = 0;
    virtual void keyRelease(char key){};
};

#endif
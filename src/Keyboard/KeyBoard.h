#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>
#include <thread>
#include <chrono>
#include <functional>
#include <windows.h>
#include <conio.h>

#include "../PollThread/PollThread.h"
#include "KeyboardFunctionality.h"

class Keyboard{
private:
    KeyboardFunctionality* instance;
    std::unordered_set<char> keysPressed;
    PollThread keyboardThread;

    void threadTask();
    void updatePressedKeys(char key);
    void checkReleasedKeys();
public:
    Keyboard(KeyboardFunctionality* instance, int pollRatePerSecond = 10);
    
    ~Keyboard();
    void end();
};

#endif
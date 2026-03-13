#include "Keyboard.h"

Keyboard::Keyboard(KeyboardFunctionality* Instance, int pollRatePerSecond) :
    instance{Instance},
    keyboardThread(pollRatePerSecond, threadTask,this/*[this](){this->threadTask();}*/){
}

Keyboard::~Keyboard(){
    keyboardThread.join();
}
void Keyboard::end(){
    keyboardThread.join();
}

void Keyboard::threadTask(){
    char key = '\0';
    while (_kbhit()){
        key = _getch();
        updatePressedKeys(key);
    }

    checkReleasedKeys();
}
void Keyboard::updatePressedKeys(char key){
    if (keysPressed.find(key) != keysPressed.end())
        return;

    instance->keyPress(key);
    keysPressed.insert(key);
}
void Keyboard::checkReleasedKeys(){
    std::unordered_set<char>::iterator it = keysPressed.begin();
    while (it != keysPressed.end()){
        if (GetAsyncKeyState(*it) == false){
            instance->keyRelease(*it);
            it = keysPressed.erase(it);
        }
        else
            it++;
    }
}
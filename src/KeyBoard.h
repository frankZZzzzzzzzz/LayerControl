#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <unordered_set>
#include <thread>
#include <chrono>
#include <functional>
#include <windows.h>
#include <conio.h>


class KeyBoard{
private:
    std::thread keyBoardThread;
    std::unordered_set<char> keysPressed;
    std::function<void(char)> keyPress;
    std::function<void(char)> keyRelease;
    std::chrono::milliseconds pollPeriod;
    bool running;

    void threadTask(){
        while (running){
            if (_kbhit()){
                char key = _getch();
                updatePressedKeys(key);
            }

            checkReleasedKeys();
            std::this_thread::sleep_for(pollPeriod);
        }
    }
    void updatePressedKeys(char key){
        if (keysPressed.find(key) != keysPressed.end())
            return;

        if (keyPress != nullptr)
            keyPress(key);
        keysPressed.insert(key);
    }
    void checkReleasedKeys(){
        for (std::unordered_set<char>::iterator it = keysPressed.begin(); it != keysPressed.end(); it++)
            if (GetAsyncKeyState(*it) == false){
                if (keyRelease != nullptr)
                    keyRelease(*it);
                keysPressed.erase(it);
            }
    }
public:
    KeyBoard(std::function<void(char)> KeyPress, 
    std::function<void(char)> KeyRelease = std::function<void(char)>(), 
    std::chrono::milliseconds PollPeriod = std::chrono::milliseconds(100)){
        running = true;
        keyPress = KeyPress;
        keyRelease = KeyRelease;
        pollPeriod = PollPeriod;

        keyBoardThread = std::thread(threadTask,this);
    }
    ~KeyBoard(){
        if (running){
            running = false;
            keyBoardThread.join();
        }
    }
    void end(){
        if (running){
            running = false;
            keyBoardThread.join();
        }
    }
};

#endif
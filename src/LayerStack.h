#ifndef LAYER_STACK
#define LAYER_STACK

#include <forward_list>
#include <thread>
#include <chrono>

#include "Layer.h"
#include "KeyBoard.h"

class LayerStack{
private:
    static KeyBoard* keyboard;
    static std::forward_list<Layer*> LayerOrder;

    static std::thread runningThread;
    static std::chrono::milliseconds refreshPeriod;
    static bool running;

    static void threadTask(){
        while (running){
            run();
            std::this_thread::sleep_for(refreshPeriod);
        }
    }
public:
    static void init(bool haveKeyboardInputs = true, int applicationRefreshPerSecond = 20, int keyboardRefreshPerSecond = 20){
        if (haveKeyboardInputs){
            keyboard = new KeyBoard(keyPressed,keyReleased, std::chrono::milliseconds(1000/keyboardRefreshPerSecond));
        }
        running = true;
        refreshPeriod = std::chrono::milliseconds(1000/applicationRefreshPerSecond);
        runningThread = std::thread(threadTask);
    }
    static void shutdown(){
        running = false;
        runningThread.join();
        delete keyboard;

        for (Layer* layer : LayerOrder)
            delete layer;
        LayerOrder.clear();
    }
    
    static void addLayer(Layer* layer){
        LayerOrder.push_front(layer);
    }
    
    static void removeLayer() {
        LayerOrder.pop_front();
    }

    static void replaceLayer(Layer* layer){
        LayerOrder.front() = layer;
    }

    
    static void keyPressed(char key){
        std::forward_list<Layer*>::iterator it = LayerOrder.begin();
        if (it != LayerOrder.end())
            (*(*it)).keyPressed(key);
    }
    static void keyReleased(char key){
        std::forward_list<Layer*>::iterator it = LayerOrder.begin();
        if (it != LayerOrder.end())
            (*(*it)).keyReleased(key);
    }

    static void run(){
        std::forward_list<Layer*>::iterator it = LayerOrder.begin();
        
        while (it != LayerOrder.end() && (*(*it)).isTransparent){
            (*(*it)).display();
            it++;
        }

        if (it != LayerOrder.end())
            (*(*it)).run();
    }
    
    static bool isRunning(){
        return(running);
    }
};

#endif
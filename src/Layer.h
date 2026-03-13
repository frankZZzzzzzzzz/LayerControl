#ifndef LAYER
#define LAYER

#include <forward_list>

#include "LayerStack.h"

class Layer{
private:
    bool running;
public:
    Layer ();

    void stopLayer();
    virtual void keyPressed(char key){};
    virtual void keyReleased(char key){};
    virtual void run() = 0;

    bool isRunning(){
        return(running);
    }
};

#endif
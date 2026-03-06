#ifndef LAYER
#define LAYER

#include <forward_list>

#include "LayerStack.h"

class Layer{
public:
    bool isTransparent;
    Layer (bool isTransparent = false)
    : isTransparent{isTransparent}{
        if (!LayerStack::isRunning()){
            LayerStack::init();
            LayerStack::addLayer(this);
        }
    }

    void removeThisLayer(){
        LayerStack::removeLayer();
    }
    void replaceThisLayer(Layer *otherLayer){
        LayerStack::replaceLayer(otherLayer);
    }
    virtual void keyPressed(char key){};
    virtual void keyReleased(char key){};
    virtual void display(){};
};

#endif
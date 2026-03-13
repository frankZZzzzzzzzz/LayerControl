#include "LayerStack.h"
#include "Layer.h"   
#include "PollThread.h"

LayerStack::LayerStack(bool haveKeyboardInputs, int RefreshPerSecond, int keyboardRefreshPerSecond)
: pollPeriod(1000/RefreshPerSecond){
    if (haveKeyboardInputs) {
        keyboard = std::make_unique<Keyboard>(this, keyboardRefreshPerSecond);
    }
}
LayerStack::~LayerStack() {
    for (Layer* layer : LayerOrder)
        delete layer;
    LayerOrder.clear();
    keyboard->end();
}

void LayerStack::addLayer(Layer* layer) {
    LayerOrder.push_front(layer);
}

void LayerStack::deleteFrontLayer() {
    if (LayerOrder.empty())
        return;
    
    LayerOrder.pop_front();
}

void LayerStack::replaceLayer(Layer* layer) {
    if (!LayerOrder.empty()) {
        Layer* previousLayer = LayerOrder.front();
        LayerOrder.front() = layer;
        delete previousLayer;
    } else {
        addLayer(layer);
    }
}
void LayerStack::keyPress(char key) {
    if (!LayerOrder.empty())
        LayerOrder.front()->keyPressed(key);
}

void LayerStack::keyRelease(char key) {
    if (!LayerOrder.empty())
        LayerOrder.front()->keyReleased(key);
}

void LayerStack::run() {
    auto later = std::chrono::steady_clock::now();
    running = true;
    while (running){
        if (!LayerOrder.empty()){
            Layer* layer = LayerOrder.front();
            if (layer->isRunning())
                LayerOrder.front()->run();
            else
                deleteFrontLayer();
        }
        later += std::chrono::seconds(2);
        std::this_thread::sleep_until(later);
    }
}
bool LayerStack::isRunning(){
    return(running);
}
void LayerStack::stopRunning(){
    running = false;
}
#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include <forward_list>
#include <thread>
#include <chrono>
#include <memory>
#include <atomic>

#include "Keyboard/Keyboard.h"
#include "Keyboard/KeyboardFunctionality.h"

// Forward declarations to avoid circular includes
class Layer;
class PollThread;

class LayerStack : public KeyboardFunctionality{
private:
    std::forward_list<Layer*> LayerOrder;
    std::unique_ptr<Keyboard> keyboard;
    std::chrono::milliseconds pollPeriod;
    std::atomic<bool> running;
public:
    LayerStack(bool haveKeyboardInputs = true, int RefreshPerSecond = 1, int keyboardRefreshPerSecond = 20);
    ~LayerStack();

    void addLayer(Layer* layer);
    void deleteFrontLayer();
    void replaceLayer(Layer* layer);

    void keyPress(char key);
    void keyRelease(char key);
    void run();

    bool isRunning();
    void stopRunning();
};

#endif
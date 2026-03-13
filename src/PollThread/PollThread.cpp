#include "PollThread.h"


PollThread::~PollThread(){
    if (running)
        join();
}
bool PollThread::isRunning(){
    return(running);
}
void PollThread::join(){
    running = false;

    if (runningThread.joinable())
        runningThread.join();
}
void PollThread::detach(){
    if (runningThread.joinable())
        runningThread.detach();
}
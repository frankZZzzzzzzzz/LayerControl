#ifndef POLLTHREAD
#define POLLTHREAD

#include <thread>
#include <functional>
#include <chrono>
#include <atomic>

class PollThread{
private:
    std::chrono::milliseconds pollPeriod;
    std::thread runningThread;
    std::atomic<bool> running;

public:
    template<typename function, typename ...argTypes>
    PollThread(int RatePerSecond, function func, argTypes ...args) : 
        running{true},
        pollPeriod{std::chrono::milliseconds((long long)(1000.0f/RatePerSecond))},
        runningThread{[this, func, args...](){this->ThreadTask(func,args...);}}{
    }


    template<typename function, typename ...argTypes>
    void ThreadTask(function func, argTypes ...args){
        std::chrono::steady_clock::time_point next = std::chrono::steady_clock::now();
        while (running){
            std::invoke(func,args...);

            next += pollPeriod;
            std::this_thread::sleep_until(next);
        }
    }
    ~PollThread();
    bool isRunning();
    void join();
    void detach();
};

#endif
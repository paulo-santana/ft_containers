#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

class Timer
{
    struct timeval last_tick;

public:
    Timer() {
        gettimeofday(&last_tick, 0);
    }

    Timer(const Timer &other) { 
        last_tick = other.last_tick;
    };

    Timer &operator=(const Timer &other) { 
        last_tick = other.last_tick;
        return *this;
    };

    void reset() {
        gettimeofday(&last_tick, 0);
    }

    long elapsed() {
        struct timeval curr;
        gettimeofday(&curr, 0);
        return ((curr.tv_sec - last_tick.tv_sec) * 1000000 +
                (curr.tv_usec - last_tick.tv_usec));
    }

    double elapsed_seconds() {
        return elapsed() / 1000000.0;
    }

    ~Timer() { }

};
    
#endif // !TIMER_H

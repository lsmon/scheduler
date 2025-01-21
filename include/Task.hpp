#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <string>
#include <chrono>

class Task {
public:
    // Member variable to store the task's execution time
    virtual void run() = 0;

};

#endif //__TASK_HPP__
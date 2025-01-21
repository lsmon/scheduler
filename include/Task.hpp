#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <string>
#include <chrono>

class Task {
public:
    // Member variable to store the task's execution time
    // std::chrono::system_clock::time_point execTime;

    virtual void run() = 0;

    // Member variable to store the task data (e.g., string, int, etc.)
    // std::string data;

    // Constructor with default execution time
    // Task(std::chrono::system_clock::time_point execTime) : execTime(execTime) {}

    // Constructor without explicit execution time
    // Task() : execTime{} {}

};

#endif //__TASK_HPP__
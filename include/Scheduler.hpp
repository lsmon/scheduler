#ifndef __SCHEDULER_HPP__
#define __SCHEDULER_HPP__

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "Task.hpp"

// TaskScheduler class with interval scheduling
class TasksScheduler {
private:
    // Shared queue to hold tasks
    std::queue<Task *> taskQueue;

    // Run tasks based on their scheduled execution times
    void runTasks();

protected:
    // Condition variable for waiting on task execution
    std::condition_variable cv;

    // Mutex for thread-safe access
    std::mutex mtx;

    // Interval duration (in seconds)
    const int interval = 600; // 10 minutes

    bool running = false;
    
public:
    // Constructor
    explicit TasksScheduler(int interval = 600) : interval(interval) {}

    // Destructor to clean up resources
    ~TasksScheduler();

    // Add a task to the scheduler with an execution time
    void addTask(Task* task);

    void stopScheduler();

    void startScheduler();

    bool isRunning();
};

class TaskScheduler : public TasksScheduler {
private:
    Task *task;

    void runTask();

public:
    explicit TaskScheduler(Task *task, const int interval = 60) : task(std::move(task)), TasksScheduler(interval) {}

    void stopScheduler();

    void startScheduler();

    ~TaskScheduler();
};

#endif //__SCHEDULER_HPP__
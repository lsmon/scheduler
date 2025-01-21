#include "Scheduler.hpp"

void TasksScheduler::runTasks() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait_for(lock, std::chrono::seconds(interval), [this] {return taskQueue.empty(); });

        if (!taskQueue.empty()) {
            auto task = taskQueue.front();

            // Remove the task from the queue
            taskQueue.pop();

            try {
                task->run();
            } catch (const std::exception& e) {
                // Handle task failure
                std::cerr << "Task failed: " << e.what() << std::endl;
            }
        } else {
            std::cout << "Task queue empty (SZ: " << taskQueue.size() << ")" << std::endl;
            stopScheduler();
        }
    }
}

void TasksScheduler::stopScheduler()
{
    running = false;
}

void TasksScheduler::startScheduler()
{
    running = true;
    runTasks();
}

bool TasksScheduler::isRunning()
{
    return running;
}

void TasksScheduler::addTask(Task *task) {
    std::lock_guard<std::mutex> lock(mtx);
    taskQueue.push(std::move(task));
    cv.notify_one();
}

TasksScheduler::~TasksScheduler() {
    while (!taskQueue.empty()) {
        auto task = std::move(taskQueue.front());
        taskQueue.pop();
    }
}

void TaskScheduler::runTask()
{
    while(running) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait_for(lock, std::chrono::seconds(interval));
            
        try {
            task->run();
        } catch (const std::exception& e) {
            // Handle task failure
            std::cerr << "Task failed: " << e.what() << std::endl;
        }
    }
}

void TaskScheduler::stopScheduler()
{
    running = false;
}

void TaskScheduler::startScheduler()
{
    running = true;
    runTask();
}

TaskScheduler::~TaskScheduler()
{
    running = false;
}


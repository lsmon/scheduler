#include "Scheduler.hpp"

void TasksScheduler::runTasks() {
    while (running) {
        std::unique_lock<std::mutex> lock(mtx);

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

        cv.wait_for(lock, std::chrono::seconds(interval), [this] {return taskQueue.empty(); });
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
    int count = 0;
    while(running) {
        std::unique_lock<std::mutex> lock(mtx);
            
        try {
            task->run();
        } catch (const std::exception& e) {
            // Handle task failure
            std::cerr << "Task failed: " << e.what() << std::endl;
        }
        if (count >= countLimit) {
            running = false;
        }
        count++;
        cv.wait_for(lock, std::chrono::seconds(interval));
    }
}

void TaskScheduler::setCountLimit(int countLimit)
{
    this->countLimit = countLimit;
}

int TaskScheduler::getCountLimit()
{
    return countLimit;
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

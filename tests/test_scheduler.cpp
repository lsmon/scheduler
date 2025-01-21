#include "Scheduler.hpp"
#include <iostream>

class PrintTask : public Task {
public:
    void run() override {
        auto now = std::chrono::system_clock::now();
        
        // Convert to milliseconds since epoch
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        std::cout << ms.count() << " Hello World!!" << std::endl; 
    }
};


void runTests() {
    TasksScheduler scheduler(10);

    

    std::chrono::system_clock::time_point execTime = std::chrono::system_clock::now() + std::chrono::seconds(10);
    scheduler.addTask(new PrintTask());
    scheduler.addTask(new PrintTask());
    scheduler.addTask(new PrintTask());
    
    scheduler.startScheduler();

    std::this_thread::sleep_for(std::chrono::milliseconds(20)); // Give time for tasks to complete

    scheduler.addTask(new PrintTask());
    scheduler.addTask(new PrintTask());
    scheduler.addTask(new PrintTask());

    if (!scheduler.isRunning())
        scheduler.startScheduler();
    scheduler.stopScheduler();
    
    std::cout << "Test Passed: Basic Scheduling\n";
    
}

void runTest() {
    TaskScheduler scheduler(new PrintTask(), 3);
    scheduler.startScheduler();

    std::this_thread::sleep_for(std::chrono::milliseconds(60)); // Give time for tasks to complete

    scheduler.stopScheduler();
    // if (counter == 2) {
        std::cout << "Test Passed: Basic Scheduling\n";
}


int main(int argc, char **argv) {
    runTests();
    // runTest();

    return EXIT_SUCCESS;
}
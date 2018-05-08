#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>

/// Shared resources
int forks[5] = { 0,0,0,0,0 };
std::mutex mtx;

void dinningWithoutGuard(int philosopherID) {
    Sleep(500);    //cause potentional deadlock!!!!
    if (forks[philosopherID % 5] == 0) {
        forks[philosopherID % 5] = 1;
    }
    Sleep(500);    //cause potentional deadlock!!!!
    if (forks[(philosopherID + 1) % 5] == 0) {
        forks[(philosopherID + 1) % 5] = 1;
    }

    while (true) {
        // Eet if he took two forks
        if (forks[philosopherID % 5] == 1 && forks[(philosopherID + 1) % 5] == 1) {
            //aham...aham...
            Sleep(4);
                
            break;
        }
    }

    //Send back forks
    if (forks[philosopherID % 5] == 1) {
        forks[philosopherID % 5] = 0;
    }

    if (forks[(philosopherID + 1) % 5] == 1) {
        forks[(philosopherID + 1) % 5] = 0;
    }
    std::cout << "Philosopher #" << philosopherID << " finished his meal.\n";
}

void dinningWithGuard(int philosopherID) {
    std::lock_guard<std::mutex> guard(mtx);

    Sleep(500);    //cause potentional deadlock!!!!
        
    if (forks[philosopherID % 5] == 0) {
        forks[philosopherID % 5] = 1;
    }
    Sleep(500);    //cause potentional deadlock!!!!
    if (forks[(philosopherID + 1) % 5] == 0) {
        forks[(philosopherID + 1) % 5] = 1;
    }

    while (true) {
        // Eet if he took two forks
        if (forks[philosopherID % 5] == 1 && forks[(philosopherID + 1) % 5] == 1) {
            //aham...aham...
            Sleep(4);
            break;
        }
    }

    //Send back forks
    if (forks[philosopherID % 5] == 1) {
        forks[philosopherID % 5] = 0;
    }

    if (forks[(philosopherID + 1) % 5] == 1) {
        forks[(philosopherID + 1) % 5] = 0;
    }
    std::cout << "Philosopher #" << philosopherID << " finished his meal.\n";
    
}

int main() {
    for (int i = 0; i < 4; i++) {
        memset(forks, 0, sizeof(forks));
        std::future<void> futures[5];

        for (int i = 0; i < 5; i++) {
            futures[i] = std::async(std::launch::async, dinningWithGuard, i);
            //futures[i] = std::async(std::launch::async, dinningWithoutGuard, i);
        }
    }
    system("pause");
    return 0;
}
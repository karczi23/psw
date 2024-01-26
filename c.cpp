#include <stdio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <mutex>
#include <vector>

#define SHIPS 30
#define SPACE 5
#define TUG 8

std::mutex dockMutex;
std::mutex tugMutex;

int availableSpace = SPACE;
int availableTugs = TUG;

using namespace std::this_thread;
using namespace std::chrono;
using namespace std;

struct Ship {
    
    int tugsNeeded;
    int i;
    
    // constructor
    Ship(int _i) {
        i = _i;
        tugsNeeded = (((rand() % 25) + 5) / 10) + 1;
        cout << "Ship " << i << " created, weight: " << weight << ", tugs needed: " << tugsNeeded << endl;
    }
    
    bool enterDock() {
        dockMutex.lock();
    
	// harbor is full
        if (availableSpace <= 0) {
            cout << "Ship " << i << " waiting for dock space, leaving harbor" << endl;
            dockMutex.unlock();
	        std::this_thread::sleep_for(milliseconds((rand() % 2000) + 1000));
	        return 0;
        }
    
        tugMutex.lock();
    
	// not enough available tugs to handle ship's arrival
        if (tugsNeeded > availableTugs) {
            cout << "Ship " << i << " waiting for available tugs, leaving harbor" << endl;
            tugMutex.unlock();
            dockMutex.unlock();
	        std::this_thread::sleep_for(milliseconds((rand() % 2000) + 1000));
	        return 0;
        }
    
        availableTugs -= tugsNeeded;
        availableSpace--;

        tugMutex.unlock();
        dockMutex.unlock();
        
	    cout << "Ship " << i << " is getting unpacked" << endl;
        std::this_thread::sleep_for(seconds(10));
        
	    tugMutex.lock();
        availableTugs += tugsNeeded;
        tugMutex.unlock();
        
	    cout << "Ship " << i << ": unpacking done" << endl;
        return 1;
    }
    
    void leaveDock() {
        cout << "Ship " << i << " leaving harbor" << endl;
        dockMutex.lock();
        availableSpace++;
        dockMutex.unlock();
        
        cout << "Ship " << i << " left the harbor" << endl;
    }
};

void threadFn(int i) {
    Ship ship = Ship(i);
    do {
	    cout << "Ship " << i << " entering dock" << endl;
    } while (!ship.enterDock());
    int sleepTime = (rand() % 13) + 2;
    cout << "Ship " << i << " sleeping for " << sleepTime << " seconds" << endl;
    sleep_for(seconds(sleepTime));
    ship.leaveDock();
}

int main() {
    
    vector<thread> threads;

    // init pseudorandom number generator
    srand(time(NULL));
    
    for (int i = 0; i < SHIPS; i++) {
        threads.push_back(thread(threadFn, i));
        int sleepBetweenSpawns = (rand() % 5) + 1;
        cout << "Spawning thread in " << sleepBetweenSpawns << " seconds" << endl;
        sleep_for(seconds(sleepBetweenSpawns));
    }
	
    for (thread & t: threads) {
        t.join();
    }

    return 0;
}

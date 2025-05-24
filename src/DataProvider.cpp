#include "include/DataProvider.hpp"
#include "include/SystemCall.hpp"
#include <thread>
#include <iostream>

DataProvider* DataProvider::instance = nullptr;
DataProvider::DataProvider(QObject *parent) : MyObject(parent){
}

DataProvider::~DataProvider(){

}

DataProvider* DataProvider::getInstance(QObject* parent) {
    if(instance == nullptr){
        instance = new DataProvider(parent);
    }
    return instance;
}

void DataProvider::loop(){
    while(isRunning){
        std::cout << "DataProvider loop" << std::endl;
        SystemCall* sysCall = SystemCall::getInstance();
        if (sysCall->isAccessible()){
            std::vector<ProcessInfo> processes = sysCall->getProcesses();
            if (processes.size() == 0) { sysCall->delay = delay = 10; }    
            else {
                emit processListUpdated(processes);
            }       
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(delay != DEFAULT_DELAY) { delay = DEFAULT_DELAY; }
    }
}


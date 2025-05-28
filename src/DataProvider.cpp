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
    // ideia: não atualizar toda a lista, e sim pegar o processo pelo id e atualizar seus parâmetros.
    //talvez isso norteie onde esta o erro de segmentation fault
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


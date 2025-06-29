#include "include/DataProvider.hpp"
#include "include/SystemCallProcesses.hpp"
#include "include/SystemCallMemory.hpp"
#include "include/SystemCallCPU.hpp"

#include <thread>

DataProvider* DataProvider::instance = nullptr;
DataProvider::DataProvider(QObject *parent) : MyObject(parent){
    nameMyObject = "DataProvider";
    isRunning = false;
    delay = 600;
}

DataProvider::~DataProvider(){
    std::cout << "DataProvider destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
    instance = nullptr; // Clear the singleton instance
}

DataProvider* DataProvider::getInstance(QObject* parent) {
    if(instance == nullptr){
        instance = new DataProvider(parent);
    }
    return instance;
}


void DataProvider::loop() {
    while (isRunning) {
        SystemCallCPU* sysCallCPU = SystemCallCPU::getInstance();
        SystemCallMemory* sysCallMemory = SystemCallMemory::getInstance();
        SystemCallProcesses* sysCallProcesses = SystemCallProcesses::getInstance();


        std::vector<ProcessInfo*> processList;
        std::vector<CPUInfo*> cpuList;
        std::vector<MemoryInfo*> memoryList;

        if (sysCallProcesses != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de processos
            if(sysCallProcesses->isAccessible()) {
                for (auto& base : sysCallProcesses->getInfo()) {
                    ProcessInfo* p = dynamic_cast<ProcessInfo*>(base);
                    if (p) processList.push_back(p);
                }
                if (processList.size() > 0)
                    emit processListUpdated(processList);
            }
        }
    

        if(sysCallMemory != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de memória
            if (sysCallMemory->isAccessible()){
                for (auto& base : sysCallMemory->getInfo()) {
                    MemoryInfo* m = dynamic_cast<MemoryInfo*>(base);
                    if (m) memoryList.push_back(m);
                }
                if (memoryList.size() > 0)
                    emit memoryListUpdated(memoryList);
            }
        }


        if (sysCallCPU != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de CPU
            if (sysCallCPU->isAccessible()){
                for (auto& base : sysCallCPU->getInfo()) {
                    CPUInfo* c = dynamic_cast<CPUInfo*>(base);
                    if (c) cpuList.push_back(c);
                }
                if (memoryList.size() > 0)
                    emit cpuListUpdated(cpuList);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

const ProcessInfo* DataProvider::getProcessByPID(const std::string& pid) const {
    SystemCallProcesses* sysCallProcesses = SystemCallProcesses::getInstance();
    if (!sysCallProcesses->isAccessible()) return nullptr;

    for (auto& base : sysCallProcesses->getInfo()) {
        ProcessInfo* process = dynamic_cast<ProcessInfo*>(base);
        if (process && process->pid == pid) {
            return process;
        }
    }
    return nullptr;
}
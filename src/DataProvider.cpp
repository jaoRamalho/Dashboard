#include "include/DataProvider.hpp"
#include "include/SystemCallProcesses.hpp"
#include "include/SystemCallMemory.hpp"
#include "include/SystemCallCPU.hpp"
#include "include/SystemCallDisk.hpp"
#include "include/SystemCallFiles.hpp"
#include "include/MyMutex.hpp"

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
        SystemCallDisk* sysCallDisk = SystemCallDisk::getInstance();
        SystemCallFiles* sysCallFiles = SystemCallFiles::getInstance();

        std::vector<ProcessInfo> processList;
        std::vector<CPUInfo> cpuList;
        std::vector<MemoryInfo> memoryList;
        std::vector<PartitionInfo> diskList;
        std::vector<FileSystemNode> filesList;

        if (sysCallFiles != nullptr){
            if(sysCallFiles->isAccessible()) {
                for (auto& base : sysCallFiles->getInfo()) {
                    FileSystemNode* p = dynamic_cast<FileSystemNode*>(base);
                    if (p) filesList.push_back(*p);
                }
                if (!filesList.empty()) {
                    emit filesListUpdated(filesList);
                }
            }
        }
        
        if (sysCallProcesses != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex);
            if(sysCallProcesses->isAccessible()) {
                for (const auto& p : sysCallProcesses->getInfo()) {
                    ProcessInfo* process = dynamic_cast<ProcessInfo*>(p);
                    if (process) {
                        processList.push_back(*process);
                    }
                }
                if (!processList.empty()) {
                    emit processListUpdated(processList);
                }
            }
        }

        if (sysCallDisk != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex);
            if(sysCallDisk->isAccessible()) {
                for (auto& base : sysCallDisk->getInfo()) {
                    PartitionInfo* p = dynamic_cast<PartitionInfo*>(base);
                    if (p) diskList.push_back(*p);
                }
                if (!diskList.empty()) {
                    emit diskListUpdated(diskList);
                }
            }
        }

        if(sysCallMemory != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex);
            if (sysCallMemory->isAccessible()){
                for (auto& base : sysCallMemory->getInfo()) {
                    MemoryInfo* m = dynamic_cast<MemoryInfo*>(base);
                    if (m) memoryList.push_back(*m);
                }
                if (!memoryList.empty()){
                    emit memoryListUpdated(memoryList);
                }
            }
        }

        if (sysCallCPU != nullptr){
            std::lock_guard<std::mutex> lock(globalMutex);
            if (sysCallCPU->isAccessible()){
                for (auto& base : sysCallCPU->getInfo()) {
                    CPUInfo* c = dynamic_cast<CPUInfo*>(base);
                    if (c) cpuList.push_back(*c);
                }
                if (!cpuList.empty()) {
                    emit cpuListUpdated(cpuList);
                }
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
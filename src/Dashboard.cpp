#include "include/Dashboard.hpp"


Dashboard::Dashboard() {
    threadManager = new ThreadManager();
    sysCallMemory = SystemCallMemory::getInstance();
    sysCallProcesses = SystemCallProcesses::getInstance();
    sysCallCPU = SystemCallCPU::getInstance();
    dataProvider = DataProvider::getInstance();
}

Dashboard::~Dashboard() {
    stop();
}

void Dashboard::start() {
    threadManager->startNewThread(sysCallMemory);
    threadManager->startNewThread(sysCallProcesses);
    threadManager->startNewThread(sysCallCPU);
    threadManager->startNewThread(dataProvider);
}

void Dashboard::stop() {
    sysCallCPU->stop();
    sysCallMemory->stop();
    sysCallProcesses->stop();
    dataProvider->stop();
    threadManager->stopAll();
}
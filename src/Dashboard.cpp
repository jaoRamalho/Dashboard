#include "include/Dashboard.hpp"


Dashboard::Dashboard() {
    threadManager = new ThreadManager();
    sysCallMemory = SystemCallMemory::getInstance();
    sysCallProcesses = SystemCallProcesses::getInstance();
    sysCallCPU = SystemCallCPU::getInstance();
    sysCallDisk = SystemCallDisk::getInstance();
    sysCallFiles = SystemCallFiles::getInstance();
    dataProvider = DataProvider::getInstance();
    
}

Dashboard::~Dashboard() {
    stop();
}

void Dashboard::start() {
    threadManager->startNewThread(sysCallMemory);
    threadManager->startNewThread(sysCallProcesses);
    threadManager->startNewThread(sysCallCPU);
    threadManager->startNewThread(sysCallDisk);
    //os arquivos sao recebidos por referencia, se colocar em thread vai travar, vai ficar realocando ate falecer
    //threadManager->startNewThread(sysCallFiles);
    threadManager->startNewThread(dataProvider);
}

void Dashboard::stop() {
    sysCallCPU->stop();
    sysCallMemory->stop();
    sysCallProcesses->stop();
    sysCallDisk->stop();
    sysCallFiles->stop();
    dataProvider->stop();
    threadManager->stopAll();
}
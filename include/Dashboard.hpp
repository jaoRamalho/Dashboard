#ifndef DASHBOARD_H
#define DASHBOARD_H


#include "ProcessInfo.h"
#include "MyObject.hpp"
#include "DataProvider.hpp"
#include "ThreadManager.hpp"
#include "SystemCall.hpp"
#include "SystemCallProcesses.hpp"
#include "SystemCallMemory.hpp"
#include "SystemCallCPU.hpp"
#include "SystemCallDisk.hpp"


class Dashboard {
private:
    ThreadManager* threadManager;
    SystemCallMemory* sysCallMemory;
    SystemCallProcesses* sysCallProcesses;
    SystemCallCPU* sysCallCPU;
    SystemCallDisk* sysCallDisk;
    DataProvider* dataProvider;
    

public:
    Dashboard();
    ~Dashboard();

    void start();
    void stop();
};

#endif // DASHBOARD_H
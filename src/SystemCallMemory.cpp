#include "include/SystemCallMemory.hpp"


SystemCallMemory* SystemCallMemory::instance = nullptr;
SystemCallMemory::SystemCallMemory(QObject* parent) : SystemCall(parent) {
    acessible = false;
    nameMyObject = "SystemCallMemory";
    delay = 600;
}

SystemCallMemory::~SystemCallMemory() {
    std::cout << "SystemCallMemory destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
    instance = nullptr; // Clear the singleton instance
}

SystemCallMemory* SystemCallMemory::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallMemory(parent);
    }
    return instance;
}

void SystemCallMemory::updateMemory() {
    //std::lock_guard<std::mutex> lock(globalMutex);
    for (InfoBase* m : info) {
        delete m;
    }
    info.clear();

    MemoryInfo* memInfo = new MemoryInfo();

    std::ifstream memFile("/proc/meminfo");
    if (memFile.is_open()) {
        std::string line;
        while (std::getline(memFile, line)) {
            if (line.rfind("MemTotal:", 0) == 0) {
                std::istringstream iss(line.substr(9));
                iss >> memInfo->total;
            } else if (line.rfind("MemFree:", 0) == 0) {
                std::istringstream iss(line.substr(8));
                iss >> memInfo->free;
            } else if (line.rfind("Buffers:", 0) == 0) {
                std::istringstream iss(line.substr(8));
                iss >> memInfo->buffers;
            } else if (line.rfind("Cached:", 0) == 0) {
                std::istringstream iss(line.substr(7));
                iss >> memInfo->cached;
            }
        }
        memInfo->used = memInfo->total - memInfo->free - memInfo->buffers - memInfo->cached;
        this->info.push_back(memInfo);
    }
}

void SystemCallMemory::loop() {
    while (isRunning) {
        acessible = false;
        updateMemory();
        acessible = true;

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}
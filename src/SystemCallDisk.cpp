#include "include/SystemCallDisk.hpp"
#include <sys/statvfs.h>
#include <set>

SystemCallDisk* SystemCallDisk::instance = nullptr;
SystemCallDisk::SystemCallDisk(QObject* parent) : SystemCall(parent){
    acessible = false;
    nameMyObject = "SystemCallDisk";
    delay = 1000; // 1 seconds
}

SystemCallDisk::~SystemCallDisk() {
    std::cout << "SystemCallDisk destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
    instance = nullptr; // Clear the singleton instance
}

SystemCallDisk* SystemCallDisk::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallDisk(parent);
    }
    return instance;
}

void SystemCallDisk::updateDiskPartitions() {
    for (auto& inst : info) delete inst;
    info.clear();

    std::ifstream partitionsFile("/proc/partitions");
    if (!partitionsFile.is_open()) return;

    std::string line;
    std::getline(partitionsFile, line); // ignora cabeçalho
    std::getline(partitionsFile, line); // ignora cabeçalho

    while (std::getline(partitionsFile, line)) {
        std::istringstream iss(line);
        int major, minor;
        unsigned long blocks;
        std::string name;

        if (!(iss >> major >> minor >> blocks >> name)) continue;

        // Ignora dispositivos base (ex: sda), queremos só partições (ex: sda1)
        if (isdigit(name.back()) == 0 && name.find("nvme") == std::string::npos)
            continue;

        auto* pi = new PartitionInfo();
        pi->device = "/dev/" + name;
        pi->totalSize = blocks * 1024UL;
        pi->usedSize = 0;
        pi->availableSize = 0;
        pi->usagePercentage = 0.0f;
        pi->isMounted = false;

        pi->mountPoint = "";
        pi->filesystemType = "";

        info.push_back(pi);
    }
}



void SystemCallDisk::loop() {
    while (isRunning) {
        acessible = false;
        updateDiskPartitions();
        acessible = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}
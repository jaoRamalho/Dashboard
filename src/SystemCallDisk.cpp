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
    std::lock_guard<std::mutex> lock(mtx);

    // Limpa as informações antigas
    for (size_t i = 0; i < info.size(); ++i) {
        PartitionInfo* p = dynamic_cast<PartitionInfo*>(info[i]);
        if (p) {
            delete p;
            info[i] = nullptr;
        }
    }
    info.clear();

    std::ifstream mountsFile("/proc/mounts");
    if (!mountsFile.is_open()) return;

    std::string line;
    while (std::getline(mountsFile, line)) {
        std::istringstream iss(line);
        std::string device, mountPoint, fsType;
        if (!(iss >> device >> mountPoint >> fsType)) continue;

        PartitionInfo* part = new PartitionInfo();
        part->device = device;
        part->mountPoint = mountPoint;
        part->filesystemType = fsType;

        struct statvfs stat;
        if (statvfs(mountPoint.c_str(), &stat) == 0) {
            unsigned long blockSize = stat.f_frsize;
            unsigned long total = stat.f_blocks * blockSize;

            if (total == 0) {
                delete part;
                continue; // Ignora partições de tamanho zero
            }

            unsigned long free = stat.f_bfree * blockSize;
            unsigned long avail = stat.f_bavail * blockSize;
            unsigned long used = total - free;

            part->totalSize = total;
            part->usedSize = used;
            part->availableSize = avail;
            part->usagePercentage = (float)used / total * 100.0f;
            part->isMounted = true;
        } else {
            delete part;
            continue; // Ignora partições que não puderam ser medidas
        }

        info.push_back(part);
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
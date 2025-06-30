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
    // Limpa info anterior
    for (auto& inst : info) delete inst;
    info.clear();

    std::ifstream partitionsFile("/proc/partitions");
    if (!partitionsFile.is_open()) return;

    std::map<std::string, std::string> mountPoints;
    std::map<std::string, std::string> fsTypes;

    // Lê pontos de montagem e tipos de FS
    std::ifstream mountsFile("/proc/mounts");
    std::string mLine;
    while (std::getline(mountsFile, mLine)) {
        std::istringstream mss(mLine);
        std::string dev, mount, fstype;
        mss >> dev >> mount >> fstype;
        if (dev.find("/dev/") == 0) {
            std::string devName = dev.substr(5); // remove "/dev/"
            mountPoints[devName] = mount;
            fsTypes[devName] = fstype;
        }
    }

    std::string line;
    std::getline(partitionsFile, line); // ignora header
    std::getline(partitionsFile, line); // ignora header

    while (std::getline(partitionsFile, line)) {
        std::istringstream iss(line);
        int major, minor;
        unsigned long blocks;
        std::string name;

        if (!(iss >> major >> minor >> blocks >> name)) continue;

        // Ignora dispositivos base como "sda", "nvme0n1" (sem número no final)
        if (isdigit(name.back()) == 0 && name.find("nvme") == std::string::npos)
            continue;

        auto* pi = new PartitionInfo();
        pi->device = "/dev/" + name;
        pi->totalSize = blocks * 1024UL;
        pi->usedSize = 0;
        pi->availableSize = 0;
        pi->usagePercentage = 0.0f;
        pi->isMounted = false;

        // Se estiver montado, calcula as informações reais de uso com statvfs
        if (mountPoints.find(name) != mountPoints.end()) {
            pi->isMounted = true;
            pi->mountPoint = mountPoints[name];
            pi->filesystemType = fsTypes[name];

            struct statvfs stat;
            if (statvfs(pi->mountPoint.c_str(), &stat) == 0) {
                pi->totalSize = stat.f_blocks * stat.f_frsize;
                pi->availableSize = stat.f_bavail * stat.f_frsize;
                pi->usedSize = pi->totalSize - pi->availableSize;
                pi->usagePercentage = (pi->totalSize > 0)
                    ? (float)pi->usedSize / pi->totalSize * 100.0f
                    : 0.0f;
            }
        }

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
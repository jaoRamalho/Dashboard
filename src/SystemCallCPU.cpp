#include "include/SystemCallCPU.hpp"


SystemCallCPU* SystemCallCPU::instance = nullptr;
SystemCallCPU::SystemCallCPU(QObject* parent) : SystemCall(parent){
    acessible = false;
    nameMyObject = "SystemCallCPU";
    delay = 200;
}

SystemCallCPU::~SystemCallCPU() {
    std::cout << "SystemCallCPU destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
    instance = nullptr; // Clear the singleton instance
}

SystemCallCPU* SystemCallCPU::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallCPU(parent);
    }
    return instance;
}
void SystemCallCPU::updateCPU() {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < (int)info.size(); i++) {
        CPUInfo* c = dynamic_cast<CPUInfo*>(info[i]);
        if (c) {
            delete c;
            info[i] = nullptr;
        }
    }

    this->info.clear();
    std::ifstream cpuFile("/proc/cpuinfo");
    if (cpuFile.is_open()) {
        std::string line;
        CPUInfo* info = nullptr;
        while (std::getline(cpuFile, line)) {
            if (line.rfind("processor", 0) == 0) {
                // Salva o anterior (se existir)
                if (info) {
                    this->info.push_back(info);
                }
                info = new CPUInfo();
                std::string value = line.substr(10);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    info->cpu = std::stoi(value);
                } catch (...) {
                    info->cpu = -1;
                }
            } else if (info && line.rfind("model name", 0) == 0) {
                info->modelName = line.substr(12);
                info->modelName.erase(0, info->modelName.find_first_not_of(" :\t"));
            } else if (info && line.rfind("model\t", 0) == 0) {
                std::string value = line.substr(6);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    info->modelNumber = std::stoi(value);
                } catch (...) {
                    info->modelNumber = -1;
                }
            } else if (info && line.rfind("cpu MHz", 0) == 0) {
                std::string value = line.substr(8);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    info->cpuMhz = std::stof(value);
                } catch (...) {
                    info->cpuMhz = 0.0;
                }
            } else if (info && line.rfind("cpu idle", 0) == 0) {
                std::ifstream statFile("/proc/stat");
                std::string line;
                if (std::getline(statFile, line)) {
                    std::istringstream iss(line);
                    std::string cpu;
                    unsigned long user, nice, system, idle;
                    iss >> cpu >> user >> nice >> system >> idle;
                    info->idleTime = idle;
                }
            } 
        }
        // Salva o último CPUInfo lido
        if (info) {
            this->info.push_back(info);
        }
    }
}

void SystemCallCPU::loop() {
    while (isRunning) {
        //std::cout << "SystemCallCPU loop" << std::endl;
        acessible = false;
        updateCPU();
        acessible = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}
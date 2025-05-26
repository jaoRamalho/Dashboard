#include "include/SystemCallCPU.hpp"


SystemCallCPU* SystemCallCPU::instance = nullptr;
SystemCallCPU::SystemCallCPU(QObject* parent) : SystemCall(parent){
    acessible = false;
    nameMyObject = "SystemCallCPU";
    delay = 600;
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
                    float tempIdleTime = (4600 - info->cpuMhz) / 46;  
                    info->idleTime = (tempIdleTime < 0) ? 0 : (unsigned long)tempIdleTime; // Garante que idleTime não seja negativ
                } catch (...) {
                    info->cpuMhz = 0.0;
                    info->idleTime = 0;
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
        acessible = false;
        updateCPU();
        acessible = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}
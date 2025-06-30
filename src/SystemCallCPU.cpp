#include "include/SystemCallCPU.hpp"
#include "include/MyMutex.hpp"


SystemCallCPU* SystemCallCPU::instance = nullptr;
SystemCallCPU::SystemCallCPU(QObject* parent) : SystemCall(parent){
    acessible = false;
    nameMyObject = "SystemCallCPU";
    delay = 600;
}

SystemCallCPU::~SystemCallCPU() {
    std::cout << "SystemCallCPU destructor called" << std::endl;
    isRunning = false;
    info.clear(); // unique_ptr limpa automaticamente
}

SystemCallCPU* SystemCallCPU::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallCPU(parent);
    }
    return instance;
}
void SystemCallCPU::updateCPU() {
    //std::lock_guard<std::mutex> lock(globalMutex);
    info.clear();
    std::ifstream cpuFile("/proc/cpuinfo");
    if (cpuFile.is_open()) {
        std::string line;
        std::unique_ptr<CPUInfo> cpuInfo;
        while (std::getline(cpuFile, line)) {
            if (line.rfind("processor", 0) == 0) {
                // Salva o anterior (se existir)
                if (cpuInfo) {
                    info.push_back(std::move(cpuInfo));
                }
                cpuInfo = std::make_unique<CPUInfo>();
                std::string value = line.substr(10);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    cpuInfo->cpu = std::stoi(value);
                } catch (...) {
                    cpuInfo->cpu = -1;
                }
            } else if (cpuInfo && line.rfind("model name", 0) == 0) {
                cpuInfo->modelName = line.substr(12);
                cpuInfo->modelName.erase(0, cpuInfo->modelName.find_first_not_of(" :\t"));
            } else if (cpuInfo && line.rfind("model\t", 0) == 0) {
                std::string value = line.substr(6);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    cpuInfo->modelNumber = std::stoi(value);
                } catch (...) {
                    cpuInfo->modelNumber = -1;
                }
            } else if (cpuInfo && line.rfind("cpu MHz", 0) == 0) {
                std::string value = line.substr(8);
                value.erase(0, value.find_first_not_of(" :\t"));
                try {
                    cpuInfo->cpuMhz = std::stof(value);
                    float tempIdleTime = (4600 - cpuInfo->cpuMhz) / 46;  
                    cpuInfo->idleTime = (tempIdleTime < 0) ? 0 : (unsigned long)tempIdleTime; // Garante que idleTime não seja negativ
                } catch (...) {
                    cpuInfo->cpuMhz = 0.0;
                    cpuInfo->idleTime = 0;
                }
            }
        }
        // Salva o último CPUInfo lido
        if (cpuInfo) {
            info.push_back(std::move(cpuInfo));
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
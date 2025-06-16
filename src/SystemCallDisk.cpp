#include "include/SystemCallDisk.hpp" // Assumindo que está em include/

#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/statfs.h> // Para statfs
#include <string.h>     // Para strerror
#include <thread>       // Para std::this_thread::sleep_for
#include <chrono>       // Para std::chrono::milliseconds

// Inicialização da instância singleton
SystemCallDisk* SystemCallDisk::instance = nullptr;

// Construtor privado
SystemCallDisk::SystemCallDisk(QObject* parent) : SystemCall(parent) {
    acessible = false;
    nameMyObject = "SystemCallDisk";
    delay = 5000; // Atraso de 5 segundos para atualização do disco
}

// Destrutor
SystemCallDisk::~SystemCallDisk() {
    std::cout << "SystemCallDisk destructor called" << std::endl;
    isRunning = false;
    info.clear();
    instance = nullptr; // Limpa a instância singleton
}

// Método estático para obter a instância singleton
SystemCallDisk* SystemCallDisk::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallDisk(parent);
    }
    return instance;
}

// Método para atualizar as informações de uso do disco
void SystemCallDisk::updateDisk() {
    std::lock_guard<std::mutex> lock(mtx); // Protege o acesso aos dados

    for (int i = 0; i < (int)info.size(); i++) {
        PartitionInfo* c = dynamic_cast<PartitionInfo*>(info[i]);
        if (c) {
            delete c;
            info[i] = nullptr;
        }
    }

    std::ifstream mountsFile("/proc/mounts");
    if (!mountsFile.is_open()) {
        std::cerr << "Erro ao abrir /proc/mounts" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(mountsFile, line)) {
        std::istringstream iss(line);
        std::string device, mountPoint, fsType, options;
        if (iss >> device >> mountPoint >> fsType >> options) {
            // Filtra sistemas de arquivos não relevantes (como você fez para CPU)
            // e garante que é um dispositivo em /dev
            if (fsType != "proc" && fsType != "sysfs" && fsType != "devtmpfs" &&
                fsType != "tmpfs" && fsType != "debugfs" && fsType != "fusectl" &&
                fsType != "cgroup" && device.rfind("/dev/", 0) == 0 &&
                !mountPoint.empty()) // Garante que o ponto de montagem não é vazio
            {
                PartitionInfo* pInfo = new PartitionInfo(); // Cria um novo objeto PartitionInfo
                pInfo->device = device;
                pInfo->mountPoint = mountPoint;
                pInfo->fsType = fsType;

                struct statfs stats;
                if (statfs(mountPoint.c_str(), &stats) == 0) {
                    unsigned long long blockSize = stats.f_bsize;
                    unsigned long long totalBlocks = stats.f_blocks;
                    unsigned long long freeBlocks = stats.f_bavail; // Blocos disponíveis para usuários não-root

                    // Conversão para GB (1024 * 1024 * 1024 bytes)
                    // Usamos 1ULL para garantir que a multiplicação seja de unsigned long long
                    pInfo->totalSpaceGB = (totalBlocks * blockSize) / (1024ULL * 1024ULL * 1024ULL);
                    pInfo->freeSpaceGB = (freeBlocks * blockSize) / (1024ULL * 1024ULL * 1024ULL);
                    pInfo->usedSpaceGB = pInfo->totalSpaceGB - pInfo->freeSpaceGB;

                    if (totalBlocks > 0) {
                        pInfo->usagePercent = (double)(totalBlocks - freeBlocks) * 100.0 / totalBlocks;
                    } else {
                        pInfo->usagePercent = 0.0;
                    }
                    info.push_back(pInfo); // Adiciona o ponteiro à lista
                    std::cout << "Dispositivo: " << device
                              << ", Ponto de montagem: " << mountPoint
                              << ", Tipo de sistema de arquivos: " << fsType
                              << ", Espaço total: " << pInfo->totalSpaceGB << " GB"
                              << ", Espaço livre: " << pInfo->freeSpaceGB << " GB"
                              << ", Espaço usado: " << pInfo->usedSpaceGB << " GB"
                              << ", Uso: " << pInfo->usagePercent << "%" << std::endl;
                } else {
                    std::cerr << "Erro ao obter statfs para " << mountPoint << ": " << strerror(errno) << std::endl;
                    delete pInfo; // Se houver erro, delete o objeto recém-criado
                }
            }
        }
    }
}


// Loop de atualização em thread separada
void SystemCallDisk::loop() {
    while (isRunning) {
        //std::cout << "SystemCallDisk loop" << std::endl;
        acessible = false;
        updateDisk();
        acessible = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}


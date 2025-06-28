#ifndef PROCESSINFO_H
#define PROCESSINFO_H

#include <string>
#include <vector>

#include <cstdint>

// Struct Basica de Informacao
struct InfoBase {
    virtual ~InfoBase() = default; 
};

// Structs de Informacao
/// Informacao de Threads
struct TreadsInfo : public InfoBase {
    std::string tid;
    std::string name;
    std::string user;
    unsigned long memory;
    unsigned int swichContextInvoluntary;
    unsigned int swichContextVoluntary;
    std::string state;
};

/// Informacao de Processos
struct ProcessInfo : public InfoBase {
    std::string pid;
    std::string name;
    std::string user;
    unsigned long memory;
    std::vector<std::string> threadsID;
    uint16_t n_threads;
    std::vector<TreadsInfo> threads;
    unsigned long swichContextInvoluntary;
    unsigned long swichContextVoluntary;
    std::string state;
    unsigned long stackSize;
    unsigned long heapSize;
};

/// Informacao de CPU
struct CPUInfo : public InfoBase {
    unsigned int cpu;
    std::string modelName;
    unsigned int modelNumber;
    unsigned long idleTime;
    unsigned long cpuMhz;
};

/// Informacao de Memoria
struct MemoryInfo : public InfoBase {
    unsigned long total;
    unsigned long free;
    unsigned long used;
    unsigned long buffers;
    unsigned long cached;
};


/// Informacao de Particao do Sistema de Arquivos
struct PartitionInfo : public InfoBase {
    std::string device;            // Nome do dispositivo, ex: /dev/sda1
    std::string mountPoint;        // Ponto de montagem, ex: /
    std::string filesystemType;    // Tipo de sistema de arquivos, ex: ext4
    unsigned long totalSize;       // Tamanho total da partição em bytes
    unsigned long usedSize;        // Espaço usado em bytes
    unsigned long availableSize;   // Espaço disponível em bytes
    float usagePercentage;         // Porcentagem de uso
    bool isMounted;                // Se está montada ou não
};


#endif // PROCESSINFO_H
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


#endif // PROCESSINFO_H
#ifndef PROCESSINFO_H
#define PROCESSINFO_H

struct ProcessInfo {
    std::string pid;
    std::string name;
    std::string user;
    unsigned long memory;
    std::vector<std::string> threadsID;
    uint16_t n_threads;
};

#endif // PROCESSINFO_H
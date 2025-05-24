#include "include/SystemCall.hpp"
#include <filesystem>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <iostream>
#include <thread>


SystemCall* SystemCall::instance = nullptr;
SystemCall::SystemCall(QObject* parent) : MyObject(parent){

}

SystemCall::~SystemCall(){

}


SystemCall *SystemCall::getInstance(QObject * parent){
    if (instance == nullptr){
        instance = new SystemCall(parent);
    }
    return instance;
}

void SystemCall::loop(){
    while (isRunning){
        std::cout << "SystemCall loop" << std::endl;
        DISABLE_ACCESS();
        updateProcesses();
        ENABLE_ACCESS();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if(delay != DEFAULT_DELAY) { delay = DEFAULT_DELAY; }
    }    
}

std::vector<ProcessInfo> SystemCall::getProcesses(){
    if (acessible) {
        return processes;
    } 

    return std::vector<ProcessInfo>();
}

void SystemCall::updateProcesses() {
    processes.clear();
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string pid = entry.path().filename().string();
            if (std::all_of(pid.begin(), pid.end(), ::isdigit)) {
                ProcessInfo info;
                info.pid = pid;

                // Ler nome do processo
                std::ifstream statusFile(entry.path() / "status");
                std::string line;
                while (std::getline(statusFile, line)) {
                    if (line.rfind("Name:", 0) == 0) {
                        info.name = line.substr(6);
                    }
                    if (line.rfind("Uid:", 0) == 0) {
                        std::istringstream iss(line.substr(5));
                        int uid;
                        iss >> uid;
                        struct passwd *pw = getpwuid(uid);
                        if (pw) info.user = pw->pw_name;
                    }
                    if (line.rfind("VmRSS:", 0) == 0) {
                        std::istringstream iss(line.substr(6));
                        iss >> info.memory;
                    }
                }

                // Ler threads
                std::string taskPath = entry.path().string() + "/task";
                try {
                    for (const auto& threadEntry : fs::directory_iterator(taskPath)) {
                        std::string tid = threadEntry.path().filename().string();
                        info.threadsID.push_back(tid);
                    }
                    info.n_threads = static_cast<uint16_t>(info.threadsID.size());
                } catch (const std::filesystem::filesystem_error& e) {
                    // O processo pode ter terminado, ignore o erro
                }

                processes.push_back(info);
            }
        }
    }
}
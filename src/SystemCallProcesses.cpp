#include "include/SystemCallProcesses.hpp"

#include <pwd.h> 
#include <sys/types.h>

SystemCallProcesses* SystemCallProcesses::instance = nullptr;
SystemCallProcesses::SystemCallProcesses(QObject* parent) : SystemCall(parent) {
    acessible = false;
    nameMyObject = "SystemCallProcesses";
    delay = 600;
}

SystemCallProcesses::~SystemCallProcesses() {
    std::cout << "SystemCallProcesses destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
    instance = nullptr; // Clear the singleton instance
}

SystemCallProcesses* SystemCallProcesses::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallProcesses(parent);
    }
    return instance;
}


std::vector<std::string> getThreadIDs(const std::string& pid) {
    std::vector<std::string> tids;
    std::string taskPath = "/proc/" + pid + "/task";
    for (const auto& entry : std::filesystem::directory_iterator(taskPath)) {
        tids.push_back(entry.path().filename());
    }
    return tids;
}

void SystemCallProcesses::updateProcesses() {
    std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < (int)info.size(); i++) {
        ProcessInfo* p = dynamic_cast<ProcessInfo*>(info[i]);
        if (p) {
            delete p;
            info[i] = nullptr;
        }
    }

    this->info.clear();
    namespace fs = std::filesystem;
    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string pid = entry.path().filename().string();
            if (std::all_of(pid.begin(), pid.end(), ::isdigit)) {
                ProcessInfo* info = new ProcessInfo();
                info->pid = pid;

                // Ler nome do processo, usuário e memória
                std::ifstream statusFile(entry.path() / "status");
                std::string line;
                while (std::getline(statusFile, line)) {
                    if (line.rfind("Name:", 0) == 0) {
                        info->name = line.substr(6);
                        info->name.erase(0, info->name.find_first_not_of(" \t"));
                    }
                    if (line.rfind("Uid:", 0) == 0) {
                        std::istringstream iss(line.substr(5));
                        int uid;
                        iss >> uid;
                        struct passwd *pw = getpwuid(uid);
                        if (pw) info->user = pw->pw_name;
                    }
                    if (line.rfind("VmRSS:", 0) == 0) {
                        std::istringstream iss(line.substr(6));
                        iss >> info->memory;
                    }
                    if (line.rfind("State:", 0) == 0) {
                        info->state = line.substr(7);
                        info->state.erase(0, info->state.find_first_not_of(" \t"));
                    }
                    if (line.rfind("voluntary_ctxt_switches:", 0) == 0) {
                        std::istringstream iss(line.substr(24));
                        iss >> info->swichContextVoluntary;
                    }
                    if (line.rfind("nonvoluntary_ctxt_switches:", 0) == 0) {
                        std::istringstream iss(line.substr(26));
                        iss >> info->swichContextInvoluntary;
                    }
                }

                // Ler threads
                std::string taskPath = entry.path().string() + "/task";
                try {
                    for (const auto& threadEntry : fs::directory_iterator(taskPath)) {
                        std::string tid = threadEntry.path().filename().string();
                        info->threadsID.push_back(tid);
                        TreadsInfo threadInfo = getThreadInfo(info->pid ,tid);
                        info->threads.push_back(threadInfo);
                    }
                    info->n_threads = static_cast<uint16_t>(info->threadsID.size());
                } catch (const std::filesystem::filesystem_error& e) {
                    // O processo pode ter terminado, ignore o erro
                }

                this->info.push_back(info);
            }
        }
    }
}

TreadsInfo SystemCallProcesses::getThreadInfo(std::string pid, std::string tid){
    TreadsInfo threadInfo;
    std::ifstream statFile("/proc/" + pid + "/task/" + tid + "/status");
    if (statFile.is_open()) {
        std::string line;
        while (std::getline(statFile, line)) {
            if (line.rfind("Name:", 0) == 0) {
                threadInfo.name = line.substr(6);
                threadInfo.name.erase(0, threadInfo.name.find_first_not_of(" \t"));
            } else if (line.rfind("Uid:", 0) == 0) {
                std::istringstream iss(line.substr(5));
                int uid;
                iss >> uid;
                struct passwd *pw = getpwuid(uid);
                if (pw) threadInfo.user = pw->pw_name;
            } else if (line.rfind("VmRSS:", 0) == 0) {
                std::istringstream iss(line.substr(6));
                iss >> threadInfo.memory;
            } else if (line.rfind("State:", 0) == 0) {
                threadInfo.state = line.substr(7);
                threadInfo.state.erase(0, threadInfo.state.find_first_not_of(" \t"));
            } else if (line.rfind("voluntary_ctxt_switches:", 0) == 0) {
                std::istringstream iss(line.substr(24));
                iss >> threadInfo.swichContextVoluntary;
            } else if (line.rfind("nonvoluntary_ctxt_switches:", 0) == 0) {
                std::istringstream iss(line.substr(26));
                iss >> threadInfo.swichContextInvoluntary;
            }
        }
    }
    threadInfo.tid = tid;
    return threadInfo;
}

void SystemCallProcesses::loop() {
    while (isRunning) {
        acessible = false;
        updateProcesses();
        acessible = true;        
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}
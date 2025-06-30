#include "include/SystemCallProcesses.hpp"
#include "include/MyMutex.hpp"

#include <pwd.h> 
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <string>


void extractRecursos(ProcessInfo& proc);
std::string parseIPPort(const std::string& hexIPPort);
std::string parseTCPState(const std::string& hexState);
std::vector<FileLockInfo> getSystemFileLocks();

SystemCallProcesses* SystemCallProcesses::instance = nullptr;
SystemCallProcesses::SystemCallProcesses(QObject* parent) : SystemCall(parent) {
    acessible = false;
    nameMyObject = "SystemCallProcesses";
    delay = 600;
}

SystemCallProcesses::~SystemCallProcesses() {
    std::cout << "SystemCallProcesses destructor called" << std::endl;
    isRunning = false;
    instance = nullptr;
    info.clear(); // unique_ptr limpa automaticamente
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
    //std::lock_guard<std::mutex> lock(globalMutex);
    info.clear();
    namespace fs = std::filesystem;
    std::vector<FileLockInfo> fileLocks = getSystemFileLocks(); // Extrai locks de arquivos do sistema

    for (const auto& entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            std::string pid = entry.path().filename().string();
            if (std::all_of(pid.begin(), pid.end(), ::isdigit)) {
                auto infoPtr = std::make_unique<ProcessInfo>();
                ProcessInfo& info = *infoPtr;
                info.pid = pid;

                extractRecursos(info); // Extrai recursos do processo
                for (const auto& lock : fileLocks) {
                    if (lock.pid == std::stoi(pid)) {
                        info.fileLock= lock; // Atribui o lock de arquivo ao processo
                        break;
                    }
                }

                // Ler nome do processo, usuário e memória
                std::ifstream statusFile(entry.path() / "status");
                std::string line;
                while (std::getline(statusFile, line)) {
                    if (line.rfind("Name:", 0) == 0) {
                        info.name = line.substr(6);
                        info.name.erase(0, info.name.find_first_not_of(" \t"));
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
                    if (line.rfind("State:", 0) == 0) {
                        info.state = line.substr(7);
                        info.state.erase(0, info.state.find_first_not_of(" \t"));
                    }
                    if (line.rfind("voluntary_ctxt_switches:", 0) == 0) {
                        std::istringstream iss(line.substr(24));
                        iss >> info.swichContextVoluntary;
                    }
                    if (line.rfind("nonvoluntary_ctxt_switches:", 0) == 0) {
                        std::istringstream iss(line.substr(26));
                        iss >> info.swichContextInvoluntary;
                    }
                    if (line.rfind("VmData:", 0) == 0) {
                        std::istringstream iss(line.substr(7));
                        iss >> info.heapSize;
                    }
                    if (line.rfind("VmStk:", 0) == 0) {
                        std::istringstream iss(line.substr(7));
                        iss >> info.stackSize;
                    }
                }

                // Ler threads
                std::string taskPath = entry.path().string() + "/task";
                try {
                    for (const auto& threadEntry : fs::directory_iterator(taskPath)) {
                        std::string tid = threadEntry.path().filename().string();
                        info.threadsID.push_back(tid);
                        TreadsInfo threadInfo = getThreadInfo(info.pid ,tid);
                        info.threads.push_back(threadInfo);
                    }
                    info.n_threads = static_cast<uint16_t>(info.threadsID.size());
                } catch (const std::filesystem::filesystem_error& e) {
                    // O processo pode ter terminado, ignore o erro
                }

                this->info.push_back(std::move(infoPtr));
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
    statFile.close();
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

void extractRecursos(ProcessInfo& proc) {
    const std::string pid = proc.pid;

    // --- Arquivos abertos ---
    std::string fdPath = "/proc/" + pid + "/fd";
    DIR* dir = opendir(fdPath.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_name[0] == '.') continue;

            std::string linkPath = fdPath + "/" + entry->d_name;
            char buf[PATH_MAX];
            ssize_t len = readlink(linkPath.c_str(), buf, sizeof(buf)-1);
            if (len != -1) {
                buf[len] = '\0';
                std::string caminho(buf);

                std::string tipo = caminho.find("socket:") != std::string::npos ? "Socket" : "Arquivo";
                proc.recursos.arquivos.push_back({caminho, tipo});
            }
        }
        closedir(dir);
    }

    // --- Sockets TCP/UDP/UNIX ---
    const std::vector<std::pair<std::string, std::string>> socketTypes = {
        { "tcp", "/proc/" + pid + "/net/tcp" },
        { "udp", "/proc/" + pid + "/net/udp" },
        { "unix", "/proc/" + pid + "/net/unix" }
    };

    for (const auto& [tipo, path] : socketTypes) {
        std::ifstream file(path);
        if (!file.is_open()) continue;

        std::string line;
        std::getline(file, line); // skip header

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string local, remote, stateHex;
            std::string dummy;

            if (tipo == "unix") {
                std::string type, state, inode, path;
                iss >> dummy >> type >> state >> dummy >> dummy >> dummy >> inode >> path;
                proc.recursos.sockets.push_back({ "UNIX", "", path, state });
            } else {
                iss >> dummy >> local >> remote >> stateHex;
                std::string localAddr = parseIPPort(local);
                std::string remoteAddr = parseIPPort(remote);
                std::string state = parseTCPState(stateHex);
                proc.recursos.sockets.push_back({ tipo, localAddr, remoteAddr, state });
            }
        }
        file.close();
    }
}

std::string parseIPPort(const std::string& hexIPPort) {
    unsigned int ipPart1, ipPart2, ipPart3, ipPart4, port;
    sscanf(hexIPPort.c_str(), "%02X%02X%02X%02X:%X", &ipPart4, &ipPart3, &ipPart2, &ipPart1, &port);
    return std::to_string(ipPart1) + "." + std::to_string(ipPart2) + "." +
           std::to_string(ipPart3) + "." + std::to_string(ipPart4) + ":" +
           std::to_string(port);
}

std::string parseTCPState(const std::string& hexState) {
    int state;
    std::stringstream ss;
    ss << std::hex << hexState;
    ss >> state;

    switch (state) {
        case 1: return "ESTABLISHED";
        case 2: return "SYN_SENT";
        case 3: return "SYN_RECV";
        case 4: return "FIN_WAIT1";
        case 5: return "FIN_WAIT2";
        case 6: return "TIME_WAIT";
        case 7: return "CLOSE";
        case 8: return "CLOSE_WAIT";
        case 9: return "LAST_ACK";
        case 10: return "LISTEN";
        case 11: return "CLOSING";
        default: return "UNKNOWN";
    }
}

std::vector<FileLockInfo> getSystemFileLocks() {
    std::vector<FileLockInfo> locks;
    std::ifstream file("/proc/locks");
    if (!file.is_open()) {
        return locks;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        FileLockInfo info;
        char colon;
        
        // Exemplo de linha: 
        // 1: POSIX  ADVISORY  WRITE 13053 103:04:2382608 1073741824 1073742335
        if (!(iss >> info.id >> colon >> info.tipo >> info.modo >> info.acesso >> info.pid
                  >> info.dev_inode >> info.faixaInicio >> info.faixaFim)) {
            continue; // linha mal formatada, ignora
        }

        locks.push_back(info);
    }
    file.close();
    return locks;
}


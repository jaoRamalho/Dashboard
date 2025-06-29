#include "include/SystemCallFiles.hpp"
#include <filesystem>
#include <sys/stat.h>
#include <pwd.h>
#include <sstream>
#include <iostream>

SystemCallFiles* SystemCallFiles::instance = nullptr;

SystemCallFiles::SystemCallFiles(QObject* parent) : SystemCall(parent) {
    acessible = false;
    nameMyObject = "SystemCallFiles";
    delay = 3000; // Ajuste conforme necessário
}

SystemCallFiles::~SystemCallFiles() {
    std::cout << "SystemCallFiles destructor called" << std::endl;
    isRunning = false;
    instance = nullptr;
}

SystemCallFiles* SystemCallFiles::getInstance(QObject* parent) {
    if (instance == nullptr) {
        instance = new SystemCallFiles(parent);
    }
    return instance;
}

// Função auxiliar para obter permissões no formato rwxr-xr--
std::string getPermissionsString(mode_t mode) {
    std::ostringstream perm;
    perm << ((mode & S_IRUSR) ? "r" : "-")
         << ((mode & S_IWUSR) ? "w" : "-")
         << ((mode & S_IXUSR) ? "x" : "-")
         << ((mode & S_IRGRP) ? "r" : "-")
         << ((mode & S_IWGRP) ? "w" : "-")
         << ((mode & S_IXGRP) ? "x" : "-")
         << ((mode & S_IROTH) ? "r" : "-")
         << ((mode & S_IWOTH) ? "w" : "-")
         << ((mode & S_IXOTH) ? "x" : "-");
    return perm.str();
}

// Função recursiva para montar a árvore de diretórios
FileSystemNode scanDirectory(const std::filesystem::path& path) {
    FileSystemNode node;
    node.fullPath = path.string();
    node.name = path.filename().string();

    struct stat st;
    if (stat(path.c_str(), &st) == 0) {
        node.isDirectory = S_ISDIR(st.st_mode);
        node.isSymlink = S_ISLNK(st.st_mode);
        node.size = st.st_size;

        struct passwd* pw = getpwuid(st.st_uid);
        node.owner = pw ? pw->pw_name : std::to_string(st.st_uid);
        node.permissions = getPermissionsString(st.st_mode);
    }

    if (node.isDirectory) {
        try {
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                node.children.push_back(scanDirectory(entry.path()));
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao acessar " << path << ": " << e.what() << std::endl;
        }
    }

    return node;
}

void SystemCallFiles::updateFileSystemTree(const std::string& rootPath) {
    //std::lock_guard<std::mutex> lock(globalMutex);

    for (auto& ptr : info) {
        delete ptr;
    }
    info.clear();

    try {
        FileSystemNode* root = new FileSystemNode(scanDirectory(rootPath));
        info.push_back(root);
    } catch (const std::exception& e) {
        std::cerr << "Erro ao escanear diretório: " << e.what() << std::endl;
    }
}

void SystemCallFiles::loop() {
    while (isRunning) {
        acessible = false;
        updateFileSystemTree("/"); // ou outro ponto de partida
        acessible = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

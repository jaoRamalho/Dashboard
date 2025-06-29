#ifndef SYSTEMCALLFILES_HPP
#define SYSTEMCALLFILES_HPP

#include "SystemCall.hpp"
#include "ProcessInfo.h" // Supondo que você salvou a struct FileSystemNode em um header separado

class SystemCallFiles : public SystemCall {
    Q_OBJECT
private:
    static SystemCallFiles* instance;
    SystemCallFiles(QObject* parent = nullptr);

public:
    static SystemCallFiles* getInstance(QObject* parent = nullptr);
    ~SystemCallFiles();

    void updateFileSystemTree(const std::string& rootPath = "/"); // Atualiza a árvore a partir de um diretório

public slots:
    void loop() override;
};

#endif // SYSTEMCALLFILES_HPP

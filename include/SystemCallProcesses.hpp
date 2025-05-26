#ifndef SYSTEMCALLPROCESSES_HPP
#define SYSTEMCALLPROCESSES_HPP

#include "SystemCall.hpp"

class SystemCallProcesses : public SystemCall{
    Q_OBJECT
private:
    static SystemCallProcesses* instance;
    SystemCallProcesses(QObject* parent = nullptr);
public:
    static SystemCallProcesses* getInstance(QObject* parent = nullptr);
    ~SystemCallProcesses();
    
    void updateProcesses();
    TreadsInfo getThreadInfo(std::string pid, std::string tid);
     

public slots:
    void loop() override;
};

#endif // SYSTEMCALLPROCESSES_HPP
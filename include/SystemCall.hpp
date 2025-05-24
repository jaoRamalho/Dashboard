#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include "MyObject.hpp"
#include <vector>
#include <string>
#include "ProcessInfo.h"


class SystemCall : public MyObject{
    Q_OBJECT
private:
    // Singleton instance
    static SystemCall* instance;
    
    volatile bool acessible; 
    std::vector<ProcessInfo> processes;
    
    #define ENABLE_ACCESS() { acessible = true; }
    #define DISABLE_ACCESS() { acessible = false;}
    
    void updateProcesses();
    
    SystemCall(QObject* parent = nullptr);
public: 
    static SystemCall* getInstance(QObject* parent = nullptr);
    ~SystemCall();
    bool isAccessible() const { return acessible; }
    std::vector<ProcessInfo> getProcesses();
    
public slots:
    void loop() override;
    
};

#endif // SYSTEMINFO_HPP

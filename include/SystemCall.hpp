#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include "ProcessInfo.h"
#include "MyObject.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <mutex>
#include "MyMutex.hpp"

class SystemCall : public MyObject{
    Q_OBJECT
protected:
    bool acessible;
    std::vector<InfoBase*> info;
    
public: 
    SystemCall(QObject* parent = nullptr);
    virtual ~SystemCall();

    bool isAccessible() const { return acessible; }
    std::vector<InfoBase*> getInfo();
};

#endif // SYSTEMINFO_HPP

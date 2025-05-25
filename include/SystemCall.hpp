#ifndef SYSTEMINFO_HPP
#define SYSTEMINFO_HPP

#include "MyObject.hpp"
#include <vector>
#include <string>
#include "ProcessInfo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <filesystem>
#include <mutex>

class SystemCall : public MyObject{
    Q_OBJECT
protected:
    std::mutex mtx;
    bool acessible;
    std::vector<InfoBase*> info;
    
public: 
    SystemCall(QObject* parent = nullptr);
    ~SystemCall();

    bool isAccessible() const { return acessible; }
    std::vector<InfoBase*> getInfo();
};

#endif // SYSTEMINFO_HPP

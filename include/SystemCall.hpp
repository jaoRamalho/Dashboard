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
#include <memory>

class SystemCall : public MyObject{
    Q_OBJECT
protected:
    bool acessible;
    std::vector<std::unique_ptr<InfoBase>> info;
    
public: 
    SystemCall(QObject* parent = nullptr);
    virtual ~SystemCall();

    bool isAccessible() const { return acessible; }
    const std::vector<std::unique_ptr<InfoBase>>& getInfo() const;
};

#endif // SYSTEMINFO_HPP

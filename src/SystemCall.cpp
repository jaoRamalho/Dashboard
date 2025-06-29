#include "include/SystemCall.hpp"

#include <pwd.h>
#include <unistd.h>
#include <thread>


SystemCall::SystemCall(QObject* parent) : MyObject(parent){

    acessible = false;
}

SystemCall::~SystemCall(){
    std::cout << "SystemCall destructor called" << std::endl;
    isRunning = false; // Ensure the loops stop
}

std::vector<InfoBase*> SystemCall::getInfo()
{
    //std::lock_guard<std::mutex> lock(globalMutex);

    if(info.size() > 0){
        return info;
    }
    return std::vector<InfoBase*>();
}
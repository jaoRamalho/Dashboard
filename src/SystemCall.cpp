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
    info.clear(); // unique_ptr limpa automaticamente
}

const std::vector<std::unique_ptr<InfoBase>>& SystemCall::getInfo() const
{
    return info;
}
#include "include/SystemCall.hpp"
#include <filesystem>
#include <fstream>
#include <pwd.h>
#include <unistd.h>
#include <iostream>
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
    if(info.size() > 0){
        return info;
    }
    return std::vector<InfoBase*>();
}
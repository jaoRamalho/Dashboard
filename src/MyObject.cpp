#include "include/MyObject.hpp"


MyObject::MyObject(QObject* parent) : QObject(parent), nameMyObject("MyObject") {
    delay = DEFAULT_DELAY;
}

MyObject::~MyObject(){

}

void MyObject::loop(){

}

void MyObject::stop(){
    isRunning = false; 
}

void MyObject::start(){
    isRunning = true; 
}

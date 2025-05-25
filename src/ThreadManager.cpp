#include "include/ThreadManager.hpp"
#include <iostream>

ThreadManager::ThreadManager(QObject* parent) : QObject(parent){
 
}

ThreadManager::~ThreadManager() {
   stopAll();
}

void ThreadManager::startNewThread(MyObject* obj){
    std::cout << "Starting thread: " << obj->getMyName() << std::endl;
    QThread* thread = new QThread();
    obj->start();
    obj->moveToThread(thread);
    connect(thread, &QThread::started, obj, &MyObject::loop);
    connect(thread, &QThread::finished, obj, &MyObject::stop);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    thread->start();
    threads.insert(std::pair<std::string, QThread*>(obj->getMyName(), thread));
}

void ThreadManager::stopAll(){
    for (auto thread : threads) {
        thread.second->quit();
        thread.second->wait();
    }

    for (auto thread : threads) {
        thread.second->deleteLater();
    }

    threads.clear();
}

void ThreadManager::stopThread(std::string id){
    threads[id]->quit();
    threads[id]->wait();
}
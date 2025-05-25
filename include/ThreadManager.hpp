#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include "MyObject.hpp"
#include <QThread>
#include <unordered_map>
#include <string>

class ThreadManager : public QObject {
    Q_OBJECT
private:
    std::unordered_map<std::string, QThread*> threads;

public:
    ThreadManager(QObject* parent = nullptr);
    ~ThreadManager();

    void startNewThread(MyObject* obj);
    void stopAll();
    void stopThread(std::string id);
};

#endif // THREADMANAGER_H

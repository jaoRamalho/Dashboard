#ifndef SYSTEMCALLMEMORY_HPP
#define SYSTEMCALLMEMORY_HPP

#include "SystemCall.hpp"


class SystemCallMemory : public SystemCall{
    Q_OBJECT
private:
    static SystemCallMemory* instance;
    SystemCallMemory(QObject* parent = nullptr);
public:
    static SystemCallMemory* getInstance(QObject* parent = nullptr);
    ~SystemCallMemory();
    
    void updateMemory();

public slots:
    void loop() override;
};


#endif // SYSTEMCALLMEMORY_HPP

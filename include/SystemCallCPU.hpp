#ifndef SYSTEMCALLCPU_HPP
#define SYSTEMCALLCPU_HPP

#include "SystemCall.hpp"

class SystemCallCPU : public SystemCall{
    Q_OBJECT
private:
    static SystemCallCPU* instance;
    SystemCallCPU(QObject* parent = nullptr);
public:
    static SystemCallCPU* getInstance(QObject* parent = nullptr);
    ~SystemCallCPU();

    void updateCPU();

public slots:
    void loop() override;
};

#endif // SYSTEMCALLCPU_HPP
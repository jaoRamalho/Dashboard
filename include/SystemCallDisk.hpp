#ifndef SYSTEMCALLDISK_HPP
#define SYSTEMCALLDISK_HPP

#include "SystemCall.hpp"

class SystemCallDisk : public SystemCall{
    Q_OBJECT
private:
    static SystemCallDisk* instance;
    SystemCallDisk(QObject* parent = nullptr);
public:
    static SystemCallDisk* getInstance(QObject* parent = nullptr);
    void updateDiskPartitions();
    ~SystemCallDisk();

    void updateCPU();

public slots:
    void loop() override;
};

#endif // SYSTEMCALLDISK_HPP
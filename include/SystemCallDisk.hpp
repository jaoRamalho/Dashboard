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
    ~SystemCallDisk();
    void updateDisk();

public slots:
    void loop() override;
};

#endif // SYSTEMCALLDISK_HPP
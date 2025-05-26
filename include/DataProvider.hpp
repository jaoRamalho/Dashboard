#ifndef DATAPROVIDER_HPP
#define DATAPROVIDER_HPP


#include "MyObject.hpp"
#include "ProcessInfo.h"

#include <vector>
#include <string>


class DataProvider : public MyObject{
    Q_OBJECT
private:
    static DataProvider* instance;

    DataProvider(QObject* parent = nullptr);
public:
    ~DataProvider();
    static DataProvider* getInstance(QObject* parent = nullptr);

public slots:
    void loop();

signals:
    void processListUpdated(const std::vector<ProcessInfo*>&);
    void cpuListUpdated(const std::vector<CPUInfo*>&);
    void memoryListUpdated(const std::vector<MemoryInfo*>&);
public:
    const ProcessInfo* getProcessByPID(const std::string& pid) const;
};

#endif // DATAPROVIDER_HPP
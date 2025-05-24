#ifndef DATAPROVIDER_HPP
#define DATAPROVIDER_HPP


#include "MyObject.hpp"
#include <vector>
#include "ProcessInfo.h"
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
    void loop() override;

signals:
    void processListUpdated(const std::vector<ProcessInfo>&);
};

#endif // DATAPROVIDER_HPP
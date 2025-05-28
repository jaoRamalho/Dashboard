#ifndef DATAPROVIDER_HPP
#define DATAPROVIDER_HPP


#include "MyObject.hpp"
#include <vector>
#include "ProcessInfo.h"
#include <string>

// data provider é resposável por ordenar a busca de dados pelo system calls, em seguida notifica a inteface de novos dados
// que devem ser mostrados na tela
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
// Sinal é uma estrutura do qt, todo sinal é amarrado com uma função, quando um sinal é emitido a função é chamada.
signals:
    void processListUpdated(const std::vector<ProcessInfo>&);
};

#endif // DATAPROVIDER_HPP
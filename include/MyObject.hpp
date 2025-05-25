#ifndef MYOBJECT_HPP
#define MYOBJECT_HPP

#include <QObject>
#include <vector>

#define DEFAULT_DELAY 600 //in ms

class MyObject : public QObject {
    Q_OBJECT
protected:
    bool isRunning;
    std::string nameMyObject;

public:
    MyObject(QObject* parent = nullptr);
    ~MyObject();
 
    uint16_t delay;
    std::string getMyName() const { return nameMyObject; }

public slots:
    virtual void loop();
    virtual void stop();
    virtual void start();
};



#endif //MYOBJECT_HPP


#ifndef MAIN_H
#define MAIN_H
 #include <QObject>

class MyObject : public QObject
 {
   Q_OBJECT
public:
    explicit MyObject (QObject* parent = 0) : QObject(parent) {}
    Q_INVOKABLE QString setTemp();

};

#endif // MAIN_H

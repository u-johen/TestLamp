//Базовый класс "обьект исполенния" к нему будут приводится все его наследники, при добавлении в коллекцию комманд
//Реализация метода Execute - в наследниках

#include <QByteArray>
#include <QObject>
#include <QDebug>

#ifndef EXECOBJ_H
#define EXECOBJ_H


class ExecObj : public QObject
{
public:
    ExecObj();
    virtual void Execute( QByteArray* readedData, quint16 dataLen) {}

};


#endif // EXECOBJ_H

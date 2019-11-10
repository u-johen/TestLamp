#include <QByteArray>
#include <QObject>

#ifndef EXECOBJ_H
#define EXECOBJ_H

//Базовый класс "обьект исполенния" к небу будут приводится все его наследники, при добавлении в коллекцию комманд
//Реализация метода Execute - в наследниках
class ExecObj : public QObject
{
public:
    ExecObj();
    virtual void Execute( QByteArray* readedData, quint16 dataLen) {}

};




#endif // EXECOBJ_H

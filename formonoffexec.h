//класс служит для переключения "фонаря" между состояниеми включено и выключено


#ifndef FOMONOFFEXEC_H
#define FOMONOFFEXEC_H

#include "formcoloroperator.h"
#include "execobj.h"
#include <QMainWindow>
#include <QColor>



class FormOnOffExec : public FormColorOperator
{
private:
    bool formOff;
public:
    FormOnOffExec(QMainWindow* ngdWindow, bool formOff);
     void Execute( QByteArray* readedData, quint16 dataLen);
};

#endif // FOMONOFFEXEC_H

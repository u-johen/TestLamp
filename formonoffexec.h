#include "formcoloroperator.h"
#ifndef FOMONOFFEXEC_H
#define FOMONOFFEXEC_H
#include "execobj.h"
#include <QMainWindow>
#include <QColor>



class FormOnOffExec : public FormColorOperator
{ //Служит для переключения "фонаря" между состояниеми включено и выключено
private:
    bool formOff;
public:
    FormOnOffExec(QMainWindow* ngdWindow, bool formOff);
     void Execute( QByteArray* readedData, quint16 dataLen);
};

#endif // FOMONOFFEXEC_H

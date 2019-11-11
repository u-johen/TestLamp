//абстактный класс  - содержит метод меняющий цвет фона окна

#include "execobj.h"
#include <QMainWindow>
#include <QColor>
#include <QVariant>

#ifndef FORMCOLOROPERATOR_H
#define FORMCOLOROPERATOR_H


class FormColorOperator : public ExecObj
{
protected:
  QMainWindow* mW;

  void SetColorToMW( QColor clrForSet); //Меняет цвет

};

#endif // FORMCOLOROPERATOR_H

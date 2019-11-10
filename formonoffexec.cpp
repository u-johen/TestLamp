#include "formonoffexec.h"



FormOnOffExec::FormOnOffExec(QMainWindow *mngdWindow, bool formOff)
{
    mW = mngdWindow;
    this->formOff = formOff;
}

void FormOnOffExec::Execute(QByteArray *readedData, quint16 dataLen){
//Тут передаваемые в параметрах вызова функции данные не важны - оставлены, чтобы сигнатура метода совпадала
//действие обтекта определяется   параметрами конструктора

//Вообще тот тут бублик с маком, строить логику основываясь на цвете подложки, это шатко.
//Но вроде как не серьезная вешь, поэтому пока оставлю

    QColor color =  mW->palette().background().color(); //текущий цвет
    if (formOff) { //реализация занимается отключением "фонаря"

        if (color == QColor(Qt::black))//Уже выключено
            return;
        else { //Иначе цвет в свойство окошка, и включаем черноту
            mW->setProperty("OldColor", color);
            SetColorToMW(QColor(Qt::black));
        }

    }
    else { //реализация занимается включением

        if (color != QColor(Qt::black)){//Уже включено
            QColor clr = QColor(Qt::black);
            return;
        }

        QVariant oC =  mW->property("OldColor");  //Возможно есть сохраненный цвет

        if (oC.isValid()) {//Если цвет был сохранен
           SetColorToMW(oC.value<QColor>()); //Ставим его
        }
        else
            SetColorToMW(QColor(Qt::white)); //Если цвета не нашлось - ставим белый - у нас же фонарь!

    }

}

//
//

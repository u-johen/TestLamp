#include "formpaintexec.h"

FormPaintExec::FormPaintExec(QMainWindow* mngdWindow){
    mW = mngdWindow;
}



void FormPaintExec::Execute(QByteArray* readedData, quint16 dataLen)
{

    if (dataLen >=3){ // если есть нужное кол-во данныхпробуем изготовить цвет
          // Тупо считаем что RGB - первые три байта в массиве
          quint8 R =  (*readedData)[0];
          quint8 G=  (*readedData)[1];
          quint8 B = (*readedData)[2];

//           qDebug()  << R;
//           qDebug()  << G;
//           qDebug()  << B;

          QColor color = QColor::fromRgb(R,G,B);


          //тут нужно определить включен фонарь или нет
          QColor curClr =  mW->palette().background().color(); //текущий цвет
          if (curClr!= QColor(Qt::black)) // включен
              SetColorToMW(color);
          else {//Выключен , в Т.З. нет четкого указания, надо ли игнорить команды смены цвета в этом режиме
              //так что на всякий случай меняю цвет, в который перейдет фонарь при включении
               mW->setProperty("OldColor", color);
          }
      }

}



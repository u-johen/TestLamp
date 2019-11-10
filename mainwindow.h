//до этого на QT ни чего не писал, делаю так, как стал бы делать на .NET,
//насколько это возможно применить к QT
//В .NET использовал бы делегаты, здесь их нет, поэтоуму идея состоит в том,
//что все команды обрабатываются соотвентствующим объектом - потомком ExecObj
//При обнаружениии команды,полученные из нее данные передаются в метод
//Execute( QByteArray* readedData, quint16 dataLen), который наследуется всеми потомками
// и кастомится под определенные действия
//ссылки на объекты хранятся в словаре с ключами -  командами

#define SRV_UINT_IP 2130706433 //127.0.0.1 как UINT
#define SRV_PORT 9999
#define CMD_LEN 3

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QtNetwork>
#include<iostream>
#include <QDebug>
#include "formonoffexec.h"
#include "formpaintexec.h"



namespace Ui {



class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:

    void onSokConnected();
   // void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);

    void prepRunParams(); //обработка параметров командной строки
    void chkAndPrepRcvdCmd( QDataStream* stream);
    void chkAndRcvData( QDataStream* stream);

private:

    Ui::MainWindow *ui;

      QTcpSocket *sok;
      QHostAddress host;
      qint16  port;

      int bytesNeed = 0; // чтение их сокета происходит в два этапа
      //сначала вычитывается  3 байта команды, и если команда требует дочитывания блока данных
      //bytesNeed - присваивается значение длины и пока во входном буфере не наберется эта длина -
      //читать из порта ни чего не будем. как только длина набралась - вычитываем и передаем на обработку
      //bytesNeed  - обнуляется
      ExecObj* curEo; //Команда ожидающаяя накопление блока данных

      QMap<qint8,ExecObj*> cmds; //Словарь команд
      FormOnOffExec* setOn; //Команда на ключение
      FormOnOffExec* setOff; //Выключение
      FormPaintExec* setColor; //Смену цвета



};

#endif // MAINWINDOW_H

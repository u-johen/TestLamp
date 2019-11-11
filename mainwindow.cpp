

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    sok = new QTcpSocket(this);


     connect(sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
     connect(sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
     connect(sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
     connect(sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));

//    host= QHostAddress(SRV_UINT_IP);
//    port = SRV_PORT;

    prepRunParams();//Разбатает командную строку, если находит параметры - использует,
    //если не находит  - берет по умолчанию из дефайна

    sok->connectToHost(host, port);
    setOn = new FormOnOffExec(this, false);
    setOff = new FormOnOffExec(this, true);
    setColor = new FormPaintExec(this);
    cmds = QMap<qint8,ExecObj*>();
    cmds.insert(0x12,setOn);
    cmds.insert(0x13,setOff);
    cmds.insert(0x20,setColor);

     //qDebug() << "strt";
     curEo = (ExecObj*)setOff;
     curEo->Execute(nullptr, 0);






}



MainWindow::~MainWindow()
{
    sok->disconnectFromHost();

    foreach (ExecObj* eo, cmds){
        delete eo;
    }


    delete sok;



    delete ui;
}

void MainWindow::prepRunParams(){
    host= QHostAddress(); //Адрес хоста - пока пустой
    QStringList cmdline_args = QCoreApplication::arguments();
    QString ip_str = "IPNotSet";
    QString port_str = "PortNotSet";
    QListIterator<QString> it (cmdline_args);
    while (it.hasNext()) { //Перебираем все элементы командной строки
        QString current = it.next();
         if ((current== "-ip") && (it.hasNext()))  //Если нашли ключ -ip и за ним еще есть элемент
             ip_str = it.next(); // Предполагаем, что из этого следующего элемента можно добыть ip

         if ((current== "-port") && (it.hasNext()))  //Если нашли ключ -port и за ним еще есть элемент
             port_str = it.next(); // Предполагаем, что из этого следующего элемента можно добыть номер порта

    }

    bool port_ok;
    port = port_str.toUInt( &port_ok, 10 ); //Пробуем получить номер порта

    bool host_ok =  host.setAddress(ip_str); //Пробуем получить из строки ip

    if ( (!port_ok) || (!host_ok)){ //Если ну удалось получить номер порта или получить адрес хоста
           host.setAddress(SRV_UINT_IP); // адрес по умолчанию
           port = SRV_PORT; //Порт по умолчанию
           qDebug()  <<"Use these keys to define IP and Port: -ip adr -port port";
    }

}

void MainWindow::chkAndPrepRcvdCmd( QDataStream* stream){
     if(bytesNeed!=0) //Фаза получения блока данных - команду не ждем
         return;

     quint8 cmd;
     (*stream) >> cmd;

    if (!cmds.contains(cmd)) //не найдена подходящая команда
          return;

     quint16 len;
     (*stream) >> len;

     if (len==0)  //команда без блока данных
            (cmds[cmd])->Execute(nullptr, 0); //запуск с "левыми" параметрами - все равно не используются
      else { //команда с блоком данных - придется отложить ее выполнение
            bytesNeed = len;
            curEo = cmds[cmd];
       }

}

void MainWindow::chkAndRcvData(QDataStream* stream){
    if(bytesNeed==0) //Фаза получения команды - данных не будет
        return;

   QByteArray data;
    data.resize(bytesNeed);  //как то наверное можно сразу создать нужного размера, пока не нашел
   (*stream).readRawData(data.data(), bytesNeed);

    curEo->Execute(&data, bytesNeed);
    bytesNeed = 0; //по размеру  bytesNeed определяется что ожидаем данные или команду
    curEo = nullptr; //На всякий случай, возможно понадобится где нибуть проверять на существование
}



void MainWindow::onSokConnected()
{
    qDebug()  << "Connected";

//Можно послать в эхо
//  QByteArray bts = QByteArray();

//  bts.append(0x12);
//  bts.append((char)0);
//  bts.append((char)0);

//  bts.append(0x20);
//  bts.append((char)0);
//  bts.append((char)3);
//  bts.append((char)220);
//  bts.append((char)100);
//  bts.append((char)70);

//  bts.append(0x13);
//  bts.append((char)0);
//  bts.append((char)0);
//  sok->write(bts);

}

void MainWindow::onSokDisconnected()
{

    qDebug() <<"Connection to the server is lost";
    this->close();
}

void MainWindow::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
     qDebug() <<"Connection error";
     this->close();

}

void MainWindow::onSokReadyRead(){ //сокете появились данные  - пытаемся их прочитать

   QDataStream stream(sok);
   stream.setByteOrder(QDataStream::BigEndian); //не знаю, как этот параметр ведет себя на разных платфорамах - поэтому ставлю принудительно

    while(sok->bytesAvailable()>0){

        //В этом методе содержится потенциальная проблема. Если отправитель специально пришлет блок данных с неверно указанной длиной
        //то либо данные будут интерпретеироваться как команды, либо наоборот.  так же возмоно бесконечное ожидание полного блока данных
        //В рамках существующего протокола обмена, мне кажется, проблема не решаема.

        if((bytesNeed==0)&&(CMD_LEN >sok->bytesAvailable()))  //ожидаем прихода команды в буфере меньше данных чем длина команды
             return;
        else
            chkAndPrepRcvdCmd(&stream); //Проверяем наличие команды


        if ((bytesNeed>0)&&(bytesNeed>sok->bytesAvailable()))  //ожидаем накопления полного блока данных - не накопилось
            return;
        else
            chkAndRcvData(&stream); //получение полного блока данных, передача его на исполенение


    }
}

















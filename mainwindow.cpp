#include <QDateTime>
#include <QListWidget>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

QString ip;

// Realiza a desconeção
void MainWindow::disconnect(){
    socket->disconnectFromHost();
    qDebug() << "Disconect from IP";

}

void MainWindow::listarIps(){
    QString str1;
    QByteArray array;
    QStringList list;
    QDateTime datetime;
    QListWidget* lista = new QListWidget();
    QString str;
    str1 = socket->write("list /r/n");
    socket->waitForBytesWritten();
    socket->waitForReadyRead();
    qDebug() << socket->bytesAvailable();
    while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        ui->listWidget->addItem(str);
    }
}

MainWindow::~MainWindow(){
    delete ui;
    delete socket;
}


void MainWindow::tcpConnect(){

    // Guarda o valor do IP
    ip = ui->lineIp->text();
    socket->connectToHost(ip,1234);
    if(socket->waitForConnected(3000)){
        qDebug()<< "Connected";
    }
    else{
        qDebug() << "Disconnected";
    }
}

void MainWindow::mostraTempo(int value){
    // Muda o valor do slider
    int i = value;
    QString s = QString::number(i);
    ui->labelTime->setText(s);
}

void MainWindow::getData(){
    QString str;
    QByteArray array;
    QStringList list;
    QDateTime datetime;
    qDebug() << "to get data...";
    qDebug() << socket->state();
    if(socket->state() == QAbstractSocket::ConnectedState){
        if(socket->isOpen()){
            qDebug() << "reading...";
            str = "get "+ ip + "\r\n";
            socket->write(str.toUtf8());
            socket->waitForBytesWritten();
            socket->waitForReadyRead();
            qDebug() << socket->bytesAvailable();
            std::vector<int> data;
            std::vector<int>:: iterator it = data.begin();
            std::vector<int>:: iterator itend = data.end();
            while(socket->bytesAvailable()){
                str = socket->readLine().replace("\n","").replace("\r","");
                list = str.split(" ");
                if(list.size() == 2){
                    datetime.fromString(list.at(0),Qt::ISODate);
                    str = list.at(1);
                    qDebug() << datetime << ": " << str;
                    data.push_back(str.toInt());
                    // ui->widgetPlotter(str);
                }
            }
        }
    }
}



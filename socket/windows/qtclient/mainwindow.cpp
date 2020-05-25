#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpSocket = new QUdpSocket(this);
    ClientIP = QHostAddress("127.0.0.1");
    ServerIP = QHostAddress("127.0.0.1");
    srand((unsigned)time(NULL));
    ClientPort = 1024 + rand() % (5000 - 1024);
    udpSocket->bind(ClientPort);
    ServerPort = 54000;
    connect(udpSocket,&QUdpSocket::readyRead,this, &MainWindow::DealMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::DealMessage()
{
    char buf[1024] = {0};
    udpSocket->readDatagram(buf,sizeof(buf),&ClientIP,&ClientPort);
    QString str(buf);
    ui->textBrowser->append(str);
}


void MainWindow::on_UserNameEdit_editingFinished()
{
    UserName = ui->UserNameEdit->text();
    ui->UserNameEdit->setReadOnly(true);
    udpSocket->writeDatagram(UserName.toUtf8(), ServerIP, ServerPort);
}

void MainWindow::on_SendPushButton_clicked()
{

    QString str = UserName + " : " + ui->MessageEdit->toPlainText();

    udpSocket->writeDatagram(str.toUtf8(), ServerIP, ServerPort);

    ui->MessageEdit->clear();
    ui->textBrowser->append(str);
}

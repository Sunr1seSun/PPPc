#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   void DealMessage();

private slots:

    void on_UserNameEdit_editingFinished();

    void on_SendPushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString UserName;
    QUdpSocket *udpSocket;
    QHostAddress ServerIP, ClientIP;
    quint16 ServerPort, ClientPort;
};
#endif // MAINWINDOW_H

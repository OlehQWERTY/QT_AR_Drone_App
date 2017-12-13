#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

// TCP IP QT realisation

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class MyTcpServer : public QObject
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
    int getLastData() const; // return last received value
    bool isLaunched() const; // return true in case of server is started

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();

private:
    int lastReceivedData = 0;
    bool connectedFlag = false;

    QTcpServer * mTcpServer;
    QTcpSocket * mTcpSocket;
};

#endif // MYTCPSERVER_H

#include "TcpIpServer.h"

#include <QDebug>
//#include <QCoreApplication>

MyTcpServer::MyTcpServer(QObject *parent) : QObject(parent)
{
    mTcpServer = new QTcpServer(this);

    connect(mTcpServer, &QTcpServer::newConnection, this, &MyTcpServer::slotNewConnection);

    if(!mTcpServer->listen(QHostAddress::Any, 255)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void MyTcpServer::slotNewConnection()
{
    mTcpSocket = mTcpServer->nextPendingConnection();

    mTcpSocket->write("New connection done!!! I am echo server!\r\n");
    qDebug() << "New connection done!!! I am echo server!";
    connectedFlag = true; // connected

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array = mTcpSocket->readAll(); // data that is received throw tcp/ip
        bool ok = true;
        //lastReceivedData = array.toInt(&ok); // prev error - if array.toInt not ok it broke lastReceivedData and = 0
        //qDebug() << "First: " << lastReceivedData;
        array.toInt(&ok); // make it look normal
        if(ok)//ok
        {
            lastReceivedData = array.toInt(&ok);
//            qDebug() << "sensor val slotServerRead() array.data : " << array.data();
//            qDebug() << "sensor val slotServerRead() array.toInt(&ok) : " << lastReceivedData;
            mTcpSocket->write("OK!\r\n"); // send back "OK!"
        }
    }
}

void MyTcpServer::slotClientDisconnected()
{
    connectedFlag = false; // connection false
    mTcpSocket->close();
}

int MyTcpServer::getLastData() const
{
//    qDebug() << "getLastData() sensor val: " << lastReceivedData;
    return lastReceivedData;
}

bool MyTcpServer::isLaunched() const
{
    return connectedFlag;
}

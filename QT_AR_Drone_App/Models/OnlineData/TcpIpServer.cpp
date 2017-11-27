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

    connect(mTcpSocket, &QTcpSocket::readyRead, this, &MyTcpServer::slotServerRead);
    connect(mTcpSocket, &QTcpSocket::disconnected, this, &MyTcpServer::slotClientDisconnected);
}

void MyTcpServer::slotServerRead()
{
    //std::cout << "slotServerRead" << std::endl;
    while(mTcpSocket->bytesAvailable()>0)
    {
        QByteArray array = mTcpSocket->readAll(); // data that is received throw tcp/ip
        lastReceivedData = array;
        //qDebug() << array.data();
        mTcpSocket->write("OK!\r\n"); // send back "OK!"
    }
}

void MyTcpServer::slotClientDisconnected()
{
    mTcpSocket->close();
}

QByteArray MyTcpServer::getLastData()//add
{
    return lastReceivedData;
}

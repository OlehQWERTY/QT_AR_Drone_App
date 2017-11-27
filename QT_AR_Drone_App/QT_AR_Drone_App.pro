
QT       += core gui opengl network

TARGET = QT_AR_Drone_App
TEMPLATE = app

CONFIG += c++11
#CONFIG = console # default ubuntu console

HEADERS += \
    Models/GeoMap/GeoMap.h \
    Models/GeoPoint/GeoPoint.h \
    Models/GeoPoint/GeoPointValues.h \
    Models/OnlineData/GeoCoordinates.h \
    Models/OnlineData/OnlineData.h \
    Views/widget/widget.h \
    Controllers/MainController/MainController.h \
    Models/OnlineData/TcpIpServer.h

SOURCES += \
    Models/GeoMap/GeoMap.cpp \
    Models/GeoPoint/GeoPoint.cpp \
    Models/OnlineData/GeoCoordinates.cpp \
    Models/OnlineData/OnlineData.cpp \
    Views/widget/widget.cpp \
    main.cpp \
    Controllers/MainController/MainController.cpp \
    Models/OnlineData/TcpIpServer.cpp

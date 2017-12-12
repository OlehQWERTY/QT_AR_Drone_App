
QT       += core gui opengl network

TARGET = QT_AR_Drone_App
TEMPLATE = app

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets #test the same as in automatic app with UI

CONFIG += c++11
#CONFIG = console # default ubuntu console

RC_ICONS = myappico.ico # add app icon

HEADERS += \
    Models/GeoMap/GeoMap.h \
    Models/GeoPoint/GeoPoint.h \
    Models/GeoPoint/GeoPointValues.h \
    Models/OnlineData/GeoCoordinates.h \
    Models/OnlineData/OnlineData.h \
    Views/widget/widget.h \
    Controllers/MainController/MainController.h \
    Models/OnlineData/TcpIpServer.h \
    Views/dialog/dialog.h \
    Views/inputError/inputerror.h \
    Views/dialog/appinitdata.h

SOURCES += \
    Models/GeoMap/GeoMap.cpp \
    Models/GeoPoint/GeoPoint.cpp \
    Models/OnlineData/GeoCoordinates.cpp \
    Models/OnlineData/OnlineData.cpp \
    Views/widget/widget.cpp \
    main.cpp \
    Controllers/MainController/MainController.cpp \
    Models/OnlineData/TcpIpServer.cpp \
    Views/dialog/dialog.cpp \
    Views/inputError/inputerror.cpp

FORMS += \
    Views/dialog/dialog.ui \
    Views/inputError/inputerror.ui

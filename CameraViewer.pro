QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH+=./VimbaCPP

LIBS+=./VimbaCPP/Lib/Win64/VimbaCPP.lib
LIBS+=./VimbaImageTransform/Lib\Win64/VimbaImageTransform.lib

CONFIG+=console

SOURCES += \
    Helper.cpp \
    ImageWriter.cpp \
    camerabutton.cpp \
    camerainfo.cpp \
    cameramanager.cpp \
    cameraobserver.cpp \
    frameobserver.cpp \
    imageprocessthread.cpp \
    main.cpp \
    mainwindow.cpp \
    previewlabel.cpp

HEADERS += \
    Helper.h \
    ImageWriter.h \
    camerabutton.h \
    camerainfo.h \
    cameramanager.h \
    cameraobserver.h \
    frameobserver.h \
    imageprocessthread.h \
    mainwindow.h \
    memcpy_threaded.h \
    previewlabel.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

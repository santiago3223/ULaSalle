#-------------------------------------------------
#
# Project created by QtCreator 2015-11-24T16:44:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CBIR
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glcm.cpp \
    image.cpp \
    imgfeatures.cpp \
    app.cpp

HEADERS  += mainwindow.h \
    glcm.h \
    image.h \
    imgfeatures.h \
    app.h \
    singleton.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include/opencv
INCLUDEPATH += /home/santiago/arb/arboretumR2/include/
LIBS += -L/usr/lib/ -lopencv_core -lopencv_highgui
LIBS += -L/home/santiago/arb/arboretumR2/lib/ -lstdc++ -lm -larboretum


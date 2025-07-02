#-------------------------------------------------
#
# Project created by QtCreator 2017-11-11T18:29:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimuladorTransito

TEMPLATE = app

CONFIG += c++14
QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS_RELEASE *= -O2

SOURCES +=  main.cpp\
            mainwindow.cpp \
    pista.cpp \
    veiculo.cpp \
    semaforo.cpp \
    simulacao.cpp \
    relogio.cpp \
    evento.cpp \
    simuladorview.cpp \
    carroimagem.cpp \
    semaforoimagem.cpp

HEADERS  += mainwindow.hpp \
    pista.hpp \
    veiculo.hpp \
    semaforo.hpp \
    simulacao.hpp \
    relogio.hpp \
    evento.hpp \
    simuladorview.hpp \
    carroimagem.hpp \
    semaforoimagem.hpp

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    imagens.qrc

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <simuladorview.hpp>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSobre;
    QAction *actionIniciar;
    QAction *actionPausar;
    QAction *actionParar;
    QAction *action10x;
    QAction *action100x;
    QAction *action_10x;
    QAction *action_100x;
    QWidget *centralWidget;
    SimuladorView *graphicsView;
    QLabel *label;
    QLabel *qtd_in;
    QLabel *label_2;
    QLabel *qtd_out;
    QLabel *label_3;
    QLabel *timer;
    QMenuBar *menuBar;
    QMenu *menuSobre;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1300, 720);
        MainWindow->setMinimumSize(QSize(1300, 720));
        actionSobre = new QAction(MainWindow);
        actionSobre->setObjectName(QStringLiteral("actionSobre"));
        actionIniciar = new QAction(MainWindow);
        actionIniciar->setObjectName(QStringLiteral("actionIniciar"));
        actionIniciar->setCheckable(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Imagens/GUI/Buttons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionIniciar->setIcon(icon);
        actionPausar = new QAction(MainWindow);
        actionPausar->setObjectName(QStringLiteral("actionPausar"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Imagens/GUI/Buttons/media-playback-pause.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionPausar->setIcon(icon1);
        actionParar = new QAction(MainWindow);
        actionParar->setObjectName(QStringLiteral("actionParar"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Imagens/GUI/Buttons/media-playback-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionParar->setIcon(icon2);
        action10x = new QAction(MainWindow);
        action10x->setObjectName(QStringLiteral("action10x"));
        action100x = new QAction(MainWindow);
        action100x->setObjectName(QStringLiteral("action100x"));
        action_10x = new QAction(MainWindow);
        action_10x->setObjectName(QStringLiteral("action_10x"));
        action_100x = new QAction(MainWindow);
        action_100x->setObjectName(QStringLiteral("action_100x"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        graphicsView = new SimuladorView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(40, 70, 1200, 490));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 10, 301, 21));
        qtd_in = new QLabel(centralWidget);
        qtd_in->setObjectName(QStringLiteral("qtd_in"));
        qtd_in->setGeometry(QRect(350, 13, 59, 15));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 40, 291, 16));
        qtd_out = new QLabel(centralWidget);
        qtd_out->setObjectName(QStringLiteral("qtd_out"));
        qtd_out->setGeometry(QRect(350, 40, 61, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(880, 10, 231, 31));
        timer = new QLabel(centralWidget);
        timer->setObjectName(QStringLiteral("timer"));
        timer->setGeometry(QRect(1120, 17, 81, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1300, 20));
        menuSobre = new QMenu(menuBar);
        menuSobre->setObjectName(QStringLiteral("menuSobre"));
        menuSobre->setGeometry(QRect(242, 140, 148, 69));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 30));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menuBar->addAction(menuSobre->menuAction());
        menuSobre->addAction(actionSobre);
        toolBar->addAction(actionIniciar);
        toolBar->addAction(actionPausar);
        toolBar->addAction(actionParar);
        toolBar->addAction(action10x);
        toolBar->addAction(action100x);
        toolBar->addAction(action_10x);
        toolBar->addAction(action_100x);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionSobre->setText(QApplication::translate("MainWindow", "Sobre", Q_NULLPTR));
        actionIniciar->setText(QApplication::translate("MainWindow", "Iniciar", Q_NULLPTR));
        actionPausar->setText(QApplication::translate("MainWindow", "Pausar", Q_NULLPTR));
        actionParar->setText(QApplication::translate("MainWindow", "Parar", Q_NULLPTR));
        action10x->setText(QApplication::translate("MainWindow", "+10x", Q_NULLPTR));
        action100x->setText(QApplication::translate("MainWindow", "+100x", Q_NULLPTR));
        action_10x->setText(QApplication::translate("MainWindow", "-10x", Q_NULLPTR));
        action_100x->setText(QApplication::translate("MainWindow", "-100x", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Quantidade de ve\303\255culos que entraram no sistema:", Q_NULLPTR));
        qtd_in->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Quantidade de ve\303\255culos que sa\303\255ram do sistema:", Q_NULLPTR));
        qtd_out->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Tempo de simula\303\247\303\243o (em segundos): ", Q_NULLPTR));
        timer->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        menuSobre->setTitle(QApplication::translate("MainWindow", "Ajuda", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

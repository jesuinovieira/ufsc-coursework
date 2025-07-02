#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMessageBox>

#include <QTimer>
#include <QLabel>

#include "simulacao.hpp"
#include "veiculo.hpp"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void attTimer();
    void attSemaforos();
    void attTela();

private slots:
    void on_actionSobre_triggered();
    void on_actionIniciar_triggered();
    void on_actionPausar_triggered();
    void on_actionParar_triggered();

    void on_action10x_triggered();

    void on_action100x_triggered();

    void on_action_10x_triggered();

    void on_action_100x_triggered();

private:
    Ui::MainWindow* ui;
    Simulacao* _sim;

    QTimer* _semaforoTimer;
    QTimer* _tempoTimer;
    QTimer* _viewTimer;
};

#endif // MAINWINDOW_HPP

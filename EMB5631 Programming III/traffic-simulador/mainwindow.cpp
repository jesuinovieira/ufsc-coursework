#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),
                                            ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMaximumSize(1200, 720);

    // Cria uma simulacao
    _sim = new Simulacao;

    // Cria um QTimer para ficar atualizando a tela da simulação
    _viewTimer = new QTimer(this);
    connect(_viewTimer, SIGNAL(timeout()), this, SLOT(attTela()));

    // Cria um QTimer para ficar atualizando o tempo da simulação
    _tempoTimer = new QTimer(this);
    connect(_tempoTimer, SIGNAL(timeout()), this, SLOT(attTimer()));

    // Cria um QTimer para ficar atualizando os semáforos da simulação
    _semaforoTimer = new QTimer(this);
    connect(_semaforoTimer, SIGNAL(timeout()), this, SLOT(attSemaforos()));

    ui->actionIniciar->setEnabled(true);
    ui->actionPausar->setEnabled(false);
    ui->actionParar->setEnabled(false);
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
    ui->action_10x->setEnabled(false);
    ui->action_100x->setEnabled(false);

    ui->graphicsView->drawSemaforos(1, 2);
}

MainWindow::~MainWindow()
{
    if(_sim != nullptr)                 delete _sim;
    _sim = nullptr;
    if(_semaforoTimer != nullptr)       delete _semaforoTimer;
    _semaforoTimer = nullptr;
    if(_tempoTimer != nullptr)          delete _tempoTimer;
    _tempoTimer = nullptr;
    if(_viewTimer != nullptr)           delete _viewTimer;
    _viewTimer = nullptr;
    if(ui != nullptr)                   delete ui;
    ui = nullptr;
}

void MainWindow::attTela()
{
    if(_sim->getTempoAtual() != _sim->getTempoSimulacao())
        // Atualiza a posicao dos carros na tela
        ui->graphicsView->drawCars(_sim->getListaPosVeiculos());

    else
    {
        this->on_actionParar_triggered();
        this->on_actionPausar_triggered();

        QMessageBox box(this);

        box.setText(QString::fromUtf8
                    ("A simulação terminou. Obrigado!"));
        box.setIcon(QMessageBox::NoIcon);
        box.exec();
    }
}

void MainWindow::attSemaforos()
{
    _sim->attSemaforos();

    int tmp = _sim->getSemaforoDir();

    if(tmp == 1)
        ui->graphicsView->drawSemaforos(1, 2);
    else if(tmp == 2)
        ui->graphicsView->drawSemaforos(3, 6);
    else if(tmp == 3)
        ui->graphicsView->drawSemaforos(4, 5);
    else
        ui->graphicsView->drawSemaforos(0, 7);
}

void MainWindow::attTimer()
{
    _sim->attTimer();
    _sim->execEventos();
    _sim->movimentaVeiculos();

    ui->timer->setText(QString().setNum(_sim->getTempoAtual()));
    ui->qtd_in->setText(QString().setNum(_sim->getQtdVeiculosIn()));
    ui->qtd_out->setText(QString().setNum(_sim->getQtdVeiculosOut()));
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox box(this);

    box.setText(QString::fromUtf8
                ("<p>Copyright © 2017 Simulador de Transito - por Jesuino Vieira Filho</p>")
                .arg(tr("Simulador de Transito")));
    box.setWindowTitle("Simulador de Transito");
    box.setIcon(QMessageBox::NoIcon);

    box.exec();
}

void MainWindow::on_actionIniciar_triggered()
{
    ui->actionIniciar->setEnabled(false);
    ui->actionPausar->setEnabled(true);
    ui->actionParar->setEnabled(true);
    ui->action10x->setEnabled(true);
    ui->action100x->setEnabled(true);
    ui->action_10x->setEnabled(false);
    ui->action_100x->setEnabled(false);

    _viewTimer->start(50);
    _tempoTimer->start(10);
    _semaforoTimer->start(5000);
}

void MainWindow::on_actionPausar_triggered()
{
    ui->actionIniciar->setEnabled(true);
    ui->actionPausar->setEnabled(false);
    ui->actionParar->setEnabled(true);

    _viewTimer->stop();
    _tempoTimer->stop();
    _semaforoTimer->stop();

    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
}

void MainWindow::on_actionParar_triggered()
{
    ui->actionIniciar->setEnabled(false);
    ui->actionPausar->setEnabled(true);
    ui->actionParar->setEnabled(true);
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);

    if(_sim != nullptr){
        delete _sim;
        _sim = nullptr;
    }

    if(_semaforoTimer != nullptr){
        delete _semaforoTimer;
        _semaforoTimer = nullptr;
    }

    if(_tempoTimer != nullptr){
        delete _tempoTimer;
        _tempoTimer = nullptr;
    }

    if(_viewTimer != nullptr){
        delete _viewTimer;
        _viewTimer = nullptr;
    }

    Veiculo::zerar();

    _sim = new Simulacao;

    _viewTimer = new QTimer(this);
    connect(_viewTimer, SIGNAL(timeout()), this, SLOT(attTela()));
    _viewTimer->start(10);

    _tempoTimer = new QTimer(this);
    connect(_tempoTimer, SIGNAL(timeout()), this, SLOT(attTimer()));
    _tempoTimer->start(10);

    _semaforoTimer = new QTimer(this);
    connect(_semaforoTimer, SIGNAL(timeout()), this, SLOT(attSemaforos()));
    _semaforoTimer->start(2000);
}

void MainWindow::on_action10x_triggered()
{
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
    ui->action_10x->setEnabled(true);
    ui->action_100x->setEnabled(false);

    _viewTimer->start(10);
    _tempoTimer->start(10);
    _semaforoTimer->start(500);
}

void MainWindow::on_action100x_triggered()
{
    ui->action10x->setEnabled(false);
    ui->action100x->setEnabled(false);
    ui->action_10x->setEnabled(false);
    ui->action_100x->setEnabled(true);

    _viewTimer->start(1);
    _tempoTimer->start(1);
    _semaforoTimer->start(50);
}

void MainWindow::on_action_10x_triggered()
{
    ui->action10x->setEnabled(true);
    ui->action100x->setEnabled(true);
    ui->action_10x->setEnabled(false);
    ui->action_100x->setEnabled(false);

    _viewTimer->start(100);
    _tempoTimer->start(100);
    _semaforoTimer->start(5000);
}

void MainWindow::on_action_100x_triggered()
{
    ui->action10x->setEnabled(true);
    ui->action100x->setEnabled(true);
    ui->action_10x->setEnabled(false);
    ui->action_100x->setEnabled(false);

    _viewTimer->start(100);
    _tempoTimer->start(100);
    _semaforoTimer->start(5000);
}

#include "simuladorview.hpp"

SimuladorView::SimuladorView(QWidget* parent)
    : QGraphicsView(parent)
{
    // Esta propriedade mantém o comportamento para arrastar o mouse sobre
    // a cena enquanto o botão esquerdo do mouse é pressionado.
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setFixedSize(1200, 490);

    this->zoomOut();    this->zoomOut();
    this->zoomOut();    this->zoomOut();
    this->zoomOut();    this->zoomOut();
    this->zoomOut();    this->zoomOut();
    this->zoomOut();    this->zoomOut();

    // Background
    _item = new QGraphicsPixmapItem (QPixmap::fromImage(QImage(":./Imagens/GUI/Rodovia/Rodovia.png")));
    _scene = new QGraphicsScene;

    _scene->addItem(_item);
    this->setScene(_scene);

    // Bussola
    QPixmap bussola;
    bussola.load(":./Imagens/GUI/Bussola.png");
    _scene->addPixmap(bussola);

    for(int i = 0; i < 8; i++)
        _semaforos[i] = new SemaforoImagem;

    _semaforos[0]->setPos(QPoint(400, 387));
    _semaforos[1]->setPos(QPoint(530, 388));
    _semaforos[2]->setPos(QPoint(1235, 388));
    _semaforos[3]->setPos(QPoint(1235, 250));
    _semaforos[4]->setPos(QPoint(1105, 250));
    _semaforos[5]->setPos(QPoint(400, 250));
    _semaforos[6]->setPos(QPoint(530, 250));
    _semaforos[7]->setPos(QPoint(1105, 388));

    _scene->addItem(_semaforos[0]);
    _scene->addItem(_semaforos[1]);
    _scene->addItem(_semaforos[2]);
    _scene->addItem(_semaforos[3]);
    _scene->addItem(_semaforos[4]);
    _scene->addItem(_semaforos[5]);
    _scene->addItem(_semaforos[6]);
    _scene->addItem(_semaforos[7]);

}

SimuladorView::~SimuladorView()
{
    for(auto &tmp : _carros)
        delete tmp;
    for(SemaforoImagem* tmp : _semaforos)
        delete tmp;
    delete _item;
    delete _scene;
}

void SimuladorView::wheelEvent(QWheelEvent *evento)
{
    if(evento->delta() > 0)
        this->zoomIn();
    else
        this->zoomOut();
}

void SimuladorView::zoomIn()
{
    scale(1.1, 1.1);
}

void SimuladorView::zoomOut()
{
    scale(1 / 1.1, 1 / 1.1);
}

void SimuladorView::drawCars(std::vector<Simulacao::DadosVeiculo> tmp)
{
    for(auto &aux : _carros){
        if(aux != nullptr) delete aux;
    }

    _carros.resize(tmp.size());

    for(int i = 0; i < (int)_carros.size(); i++)
    {
        _carros[i] = nullptr;

        if((tmp[i].x > 0) && (tmp[i].x < 1570) && (tmp[i].y > 0) && (tmp[i].y < 600))
        {
            _carros[i] = new CarroImagem(tmp[i].direcao, tmp[i].sentido);
//        _carros[i]->setZValue(1);
            _carros[i]->setX(tmp[i].x);
            _carros[i]->setY(tmp[i].y);
            _scene->addItem(_carros[i]);
        }
    }
}

void SimuladorView::drawSemaforos(int a, int b)
{
    for(int i = 0; i < 8; i++)
    {
        if(i == a || i == b){
            _semaforos[i]->setEstado(true);
        }
        else{
            _semaforos[i]->setEstado(false);
        }
    }
    _scene->update();
}


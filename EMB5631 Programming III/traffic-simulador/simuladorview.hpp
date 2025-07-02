#ifndef SIMULADORVIEW_HPP
#define SIMULADORVIEW_HPP

#include <QGraphicsPixmapItem>

#include <QPixmap>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QPainter>
#include <QPointF>
#include <deque>
#include <vector>
#include "carroimagem.hpp"
#include "semaforoimagem.hpp"
#include "simulacao.hpp"

class SimuladorView : public QGraphicsView
{
public:
    SimuladorView(QWidget *);
    ~SimuladorView();

    void wheelEvent(QWheelEvent*) override;
    void zoomIn();
    void zoomOut();
    void drawCars(std::vector<Simulacao::DadosVeiculo>);
    void drawSemaforos(int, int);

private:
    int m_X;
    int m_Y;

    QGraphicsItem* _item;
    QGraphicsScene* _scene;
    std::vector<CarroImagem*> _carros;
    SemaforoImagem* _semaforos[8];
};

#endif // SIMULADORVIEW_HPP

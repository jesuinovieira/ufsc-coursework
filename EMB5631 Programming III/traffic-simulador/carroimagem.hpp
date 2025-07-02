#ifndef CARROSIMAGEM_HPP
#define CARROSIMAGEM_HPP

#include <QGraphicsItem>
#include <QPainter>

class CarroImagem : public QGraphicsItem
{
public:
    CarroImagem(bool, bool);
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;

private:
    QPixmap m_carroImage;
    bool _direcao;
};

#endif // CARROSIMAGEM_HPP

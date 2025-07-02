#include "semaforoimagem.hpp"

SemaforoImagem::SemaforoImagem()
{

}

QRectF SemaforoImagem::boundingRect() const
{
    return QRectF(x(), y(), 25, 25);
}

void SemaforoImagem::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* )
{
    painter->setBrush(QBrush(_estado ? Qt::green : Qt::red));
    painter->drawEllipse(boundingRect());
}

void SemaforoImagem::setEstado(bool value)
{
    _estado = value;
}

#ifndef SEMAFOROIMAGEM_HPP
#define SEMAFOROIMAGEM_HPP

#include <QGraphicsItem>
#include <QPainter>

class SemaforoImagem : public QGraphicsItem
{
public:
    SemaforoImagem();
    QRectF boundingRect() const override;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override;
    void setEstado(bool value);

private:
    bool _estado;
};

#endif // SEMAFOROIMAGEM_HPP

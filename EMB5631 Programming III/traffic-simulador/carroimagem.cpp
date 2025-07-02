#include "carroimagem.hpp"
#include <QImage>


CarroImagem::CarroImagem(bool direcao, bool sentido)
{
    //m_carroImage.load(":./Imagens/GUI/Carros/carro_policia.png");
    _direcao = direcao;

    QImage srcImg(":./Imagens/GUI/Carros/carro_policia.png");
    QPoint center = srcImg.rect().center();
    QMatrix matrix;

    matrix.translate(center.x(), center.y());

    if(direcao)
    {
        if(sentido)
            matrix.rotate(270);
        else
            matrix.rotate(90);
    }
    else
    {
        if(sentido)
            matrix.rotate(180); // >
        else
            matrix.rotate(0);   // <
    }

    QImage dstImg = srcImg.transformed(matrix);
    m_carroImage = QPixmap::fromImage(dstImg);

    m_carroImage = m_carroImage.scaled(direcao ? 40 : 65, direcao ? 65 : 40);
}

QRectF CarroImagem::boundingRect() const
{
    return QRectF(x(), y(), m_carroImage.width(), m_carroImage.height());
}

void CarroImagem::paint(QPainter* painter, const QStyleOptionGraphicsItem* , QWidget* )
{

    painter->drawPixmap(x(), y(), m_carroImage);
}

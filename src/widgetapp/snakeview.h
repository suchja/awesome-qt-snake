#ifndef SNAKEVIEW_H
#define SNAKEVIEW_H

#include <QGraphicsItem>
#include <QObject>
#include <QPen>
#include <QBrush>

class SnakeView : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    SnakeView(const int tile_size, QPen pen, QBrush brush, QObject* parent = nullptr);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

    void updateToPosition(QPoint head, QList<QPoint> body);

private:
    const int m_tile_size;
    const QPen m_pen;
    const QBrush m_brush;

    QPointF m_head;
    QList<QPointF> m_body;
};

#endif // SNAKEVIEW_H

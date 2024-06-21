#include "snakeview.h"

#include <QPainter>

SnakeView::SnakeView(int tile_size, QPen pen, QBrush brush, QObject *parent) :
    QObject{parent},
    m_tile_size(tile_size),
    m_pen(pen),
    m_brush(brush)
{
    // probably the snake will not have more elements.
    m_body.reserve(10);
}

void SnakeView::updateToPosition(QPoint head, QList<QPoint> body)
{
    m_head = head.toPointF();

    m_body.clear();
    for (const QPoint &point : body)
    {
        m_body.append(point.toPointF());
    }

    setPos(m_head);
}

QRectF SnakeView::boundingRect() const
{
    qreal min_x = m_head.x();
    qreal min_y = m_head.y();
    qreal max_x = m_head.x();
    qreal max_y = m_head.y();

    foreach (QPointF p, m_body) {
        max_x = p.x() > max_x ? p.x() : max_x;
        max_y = p.y() > max_y ? p.y() : max_y;
        min_x = p.x() < min_x ? p.x() : min_x;
        min_y = p.y() < min_y ? p.y() : min_y;
    }

    QPointF top_left = mapFromScene(QPointF(min_x, min_y));
    QPointF bottom_right = mapFromScene(QPointF(max_x, max_y));

    QRectF bound = QRectF(top_left.x(),
                          top_left.y(),
                          bottom_right.x() - top_left.x() + m_tile_size,
                          bottom_right.y() - top_left.y() + m_tile_size);

    return bound;
}

void SnakeView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setPen(m_pen);
    painter->setBrush(m_brush);
    painter->drawPath(shape());
    painter->restore();
}

QPainterPath SnakeView::shape() const
{
    QPainterPath path;

    path.addRect(QRectF(0, 0, m_tile_size, m_tile_size));

    foreach (const QPointF current_point, m_body) {
        const QPointF item = mapFromScene(current_point);
        path.addRect(QRectF(item.x(), item.y(), m_tile_size, m_tile_size));
    }

    return path;
}

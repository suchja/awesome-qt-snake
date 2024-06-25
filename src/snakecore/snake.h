#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>

#include "snakecore.h"

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(int board_row_count, int board_column_count, int body_count = 1, QObject *parent = nullptr);

    QPoint getHead() const;
    QList<QPoint> getBody() const;
    bool isMoving() const;

    DirectionChangeResult setMoveDirection(Direction new_direction);

    void executeMove();

signals:

private:
    QPoint m_head;
    QList<QPoint> m_body;

    Direction m_move_direction;
    bool m_moved_since_last_change;

    const int m_board_row_count;
    const int m_board_column_count;
};

#endif // SNAKE_H

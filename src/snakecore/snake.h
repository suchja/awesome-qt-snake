#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>

enum class Direction;

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(int board_row_count, int board_column_count, QObject *parent = nullptr);

    QPoint getHead() const;
    QList<QPoint> getBody() const;
    bool isMoving() const;

    void setMoveDirection(Direction new_direction);
    void executeMove();

signals:

private:
    QPoint m_head;
    QList<QPoint> m_body;

    Direction m_move_direction;

    const int m_board_row_count;
    const int m_board_column_count;
};

#endif // SNAKE_H

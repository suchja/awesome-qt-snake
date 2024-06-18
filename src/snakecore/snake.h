#ifndef SNAKE_H
#define SNAKE_H

#include <QObject>
#include <QPoint>

class Snake : public QObject
{
    Q_OBJECT
public:
    explicit Snake(int board_row_count, int board_column_count, QObject *parent = nullptr);

    QPoint getHeadPosition() const;

signals:

private:
    const int m_board_row_count;
    const int m_board_column_count;

    QPoint m_head_position;
};

#endif // SNAKE_H

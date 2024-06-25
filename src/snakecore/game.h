#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QRect>

class Snake;
class FoodGenerator;
enum class Direction;
enum class DirectionChangeResult;

class Game : public QObject
{
    Q_OBJECT

public:
    explicit Game(int board_row_count, int board_column_count, int snake_body_length = 1, QObject* parent = nullptr);

    QRect getBoardDimensions() const;

    QPoint getSnakeHeadPosition() const;
    QList<QPoint> getSnakeBodyPositions() const;

    QPoint getFoodPosition() const;

    DirectionChangeResult setMoveDirection(Direction new_direction);
    void executeMove();
    bool isGameStarted();

signals:
    void isStarted();

private:
    void addOccupiedPositions(QList<QPoint>& positions) const;

    Snake* m_snake;
    FoodGenerator* m_food_generator;
    QPoint m_food;

    const int m_board_row_count;
    const int m_board_column_count;
};

#endif // GAME_H

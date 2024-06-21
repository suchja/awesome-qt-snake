#ifndef GAMEBOARDVIEW_H
#define GAMEBOARDVIEW_H

#include <QGraphicsScene>
#include <QObject>

class GameViewModel;
class SnakeView;

class GameBoardView : public QGraphicsScene
{
public:
    GameBoardView(QObject *parent = nullptr);

    void setViewModel(GameViewModel* view_model);

private:
    void initialize_scene();
    void add_snake(QPoint head, QList<QPoint> body);
    void draw_food(QPoint food);

    void updateSnake();

    GameViewModel* m_view_model;
    SnakeView* m_snake;
};

#endif // GAMEBOARDVIEW_H

#ifndef GAMEBOARDVIEW_H
#define GAMEBOARDVIEW_H

#include <QGraphicsScene>
#include <QObject>

class GameViewModel;

class GameBoardView : public QGraphicsScene
{
public:
    GameBoardView(QObject *parent = nullptr);

    void setViewModel(GameViewModel* view_model);

private:
    void initialize_scene();
    void draw_snake(QPoint head_position);

    GameViewModel* m_view_model;
};

#endif // GAMEBOARDVIEW_H

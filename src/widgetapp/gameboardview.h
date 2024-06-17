#ifndef GAMEBOARDVIEW_H
#define GAMEBOARDVIEW_H

#include <QGraphicsScene>
#include <QObject>

#include <memory>

class GameViewModel;

class GameBoardView : public QGraphicsScene
{
public:
    GameBoardView(QObject *parent = nullptr);

    void setViewModel(GameViewModel* view_model);

private:
    void initialize_scene();

    GameViewModel* m_view_model;
};

#endif // GAMEBOARDVIEW_H

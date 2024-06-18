#ifndef GAMEVIEWMODEL_H
#define GAMEVIEWMODEL_H

#include <QObject>
#include <QRect>
#include <QPoint>

#include "game.h"

class GameViewModel : public QObject
{
    Q_OBJECT
public:
    explicit GameViewModel(Game* model, QObject *parent = nullptr);

    static constexpr int getTileSize() {return m_tile_size;};

    QRect getBoardDimensions() const;
    QList<QPoint> getSnakePositions() const;

signals:

private:
    static constexpr int m_tile_size = 20;

    Game* m_game_model;
};

#endif // GAMEVIEWMODEL_H

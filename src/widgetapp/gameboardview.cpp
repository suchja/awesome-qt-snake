#include "gameboardview.h"

#include "gameviewmodel.h"

#include <QPainter>

GameBoardView::GameBoardView(QObject *parent) : QGraphicsScene{parent} {}

void GameBoardView::setViewModel(GameViewModel *view_model)
{
    m_view_model = view_model;
    initialize_scene();
}

void GameBoardView::initialize_scene()
{
    QRectF board = QRectF(m_view_model->getBoardDimensions());

    setSceneRect(board.left(), board.top(), board.width(), board.height());
    setItemIndexMethod(QGraphicsScene::NoIndex);

    // prepare and set background
    int tile_size = m_view_model->getTileSize();

    QPixmap bg(tile_size, tile_size);
    QPainter p(&bg);
    QPen gridPen(Qt::gray);

    p.setBrush(QBrush(Qt::lightGray));
    p.setPen(gridPen);

    p.drawRect(0, 0, tile_size, tile_size);

    setBackgroundBrush(QBrush(bg));
}

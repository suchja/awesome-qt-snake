#include "gameboardview.h"

#include "gameviewmodel.h"

#include <QPainter>

GameBoardView::GameBoardView(QObject *parent) : QGraphicsScene{parent} {}

void GameBoardView::setViewModel(GameViewModel *view_model)
{
    m_view_model = view_model;
    initialize_scene();
    draw_snake(m_view_model->getSnakePositions());
    draw_food(m_view_model->getFoodPosition());
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

void GameBoardView::draw_snake(QList<QPoint> snake)
{
    int tile_size = m_view_model->getTileSize();
    QPen pen(Qt::black);
    QBrush brush(Qt::green);

    foreach (const QPoint s, snake)
    {
        addRect(s.x(), s.y(), tile_size, tile_size, pen, brush);
    }
}

void GameBoardView::draw_food(QPoint food)
{
    int tile_size = m_view_model->getTileSize();
    QPen pen(Qt::white);
    QBrush brush(Qt::red);

    addRect(food.x(), food.y(), tile_size, tile_size, pen, brush);
}

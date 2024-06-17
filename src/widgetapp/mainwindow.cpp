#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gameboardview.h"
#include "gameviewmodel.h"
#include "game.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_graphics_view = new QGraphicsView(this);
    createGame();

    // connect game with UI
    m_graphics_view->setScene(m_view);
    setCentralWidget(m_graphics_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGame()
{
    Game* model = new Game(20, 20, this);
    GameViewModel* view_model = new GameViewModel(model, this);

    m_view = new GameBoardView(m_graphics_view);
    m_view->setViewModel(view_model);
}

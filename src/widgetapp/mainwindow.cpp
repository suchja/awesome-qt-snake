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

    connect(m_view_model, SIGNAL(gameStarted()), this, SLOT(startGame()));
    connect(m_view_model, SIGNAL(userMessageUpdated(UserMessages)), this, SLOT(visualizeUserMessage(UserMessages)));

    // connect game with UI
    m_graphics_view->installEventFilter(this);
    m_graphics_view->setScene(m_view);
    setCentralWidget(m_graphics_view);
    visualizeUserMessage(m_view_model->getCurrentUserMessage());
}

void MainWindow::startGame()
{
    connect(&m_timer, SIGNAL(timeout()), m_view_model, SLOT(executeMove()));
    m_timer.start(250);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGame()
{
    Game* model = new Game(20, 20, 3, this);
    m_view_model = new GameViewModel(model, this);

    m_view = new GameBoardView(m_graphics_view);
    m_view->setViewModel(m_view_model);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent *>(event);

        if (m_view_model->processKeyboardAction(keyEvent->key())) {
            // we handled keys successfully, otherwise the base class needs to do its work!
            return true;
        }
    }
    // Call base class eventFilter
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::visualizeUserMessage(UserMessages message)
{
    switch (message) {
    case UserMessages::None :
        ui->statusbar->clearMessage();
        break;
    case UserMessages::StartGame :
        ui->statusbar->showMessage("Press any arrow key to start game!");
        break;
    case UserMessages::KeyNotSupported :
        ui->statusbar->showMessage("Key is not supported!");
        break;
    case UserMessages::WrongDirection :
        ui->statusbar->showMessage("Opposite direction not allowed!");
        break;
    default:
        break;
    }
}

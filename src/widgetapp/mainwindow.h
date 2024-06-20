#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTimer>

class GameBoardView;
class GameViewModel;
enum class UserMessages;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void createGame();
    void visualizeUserMessage(UserMessages message);

    Ui::MainWindow *ui;
    QGraphicsView* m_graphics_view;

    GameBoardView* m_view;
    GameViewModel* m_view_model;
    QTimer m_timer;
};
#endif // MAINWINDOW_H

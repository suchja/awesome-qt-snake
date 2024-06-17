#include <QTest>

// add necessary includes here
#include "game.h"
#include "gameviewmodel.h"

class test_GameViewModel : public QObject
{
    Q_OBJECT

public:
    test_GameViewModel();
    ~test_GameViewModel();

private slots:
    void getBoardDimensions_shouldReturnSceneCoordinates_whenCalledAfterConstructor();
};

test_GameViewModel::test_GameViewModel() {}

test_GameViewModel::~test_GameViewModel() {}

void test_GameViewModel::getBoardDimensions_shouldReturnSceneCoordinates_whenCalledAfterConstructor() {
    // ARRANGE
    Game* game_dependency = new Game(20, 20, this);
    QRect expected(0, 0, 400, 400);

    GameViewModel sut(game_dependency);

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);

    // CLEAN UP
    // as Game is derived from QObject, it will be automatically removed once this test is removed.
}

QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"

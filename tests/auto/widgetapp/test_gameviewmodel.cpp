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
    void getSnakePositions_shouldReturnTwoSceneCoordinatesInTheCenter_whenCalledAfterConstructor();
};

test_GameViewModel::test_GameViewModel() {}

test_GameViewModel::~test_GameViewModel() {}

void test_GameViewModel::getBoardDimensions_shouldReturnSceneCoordinates_whenCalledAfterConstructor() {
    // ARRANGE
    Game game_dependency = Game(20, 20);
    QRect expected(0, 0, 400, 400);

    GameViewModel sut(&game_dependency);

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_GameViewModel::getSnakePositions_shouldReturnTwoSceneCoordinatesInTheCenter_whenCalledAfterConstructor() {
    // ARRANGE
    int tile_size = GameViewModel::getTileSize();

    Game game_dependency = Game(20, 20);
    QList<QPoint> expected;
    expected << QPoint(200, 200) << QPoint(180, 200);

    GameViewModel sut(&game_dependency);

    // ACT
    QList<QPoint> actual = sut.getSnakePositions();

    // ASSERT
    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"

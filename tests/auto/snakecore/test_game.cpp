#include <QTest>

#define QVERIFY_LIST_NOT_INCLUDES_POINT(list, point) \
do { \
    for (int i = 0; i < (list).size(); ++i) { \
        if ((list)[i] == point) { \
            QString msg = QString("Point (%1, %2) included in list at position %3 (%4, %5)") \
                  .arg(point.x()).arg(point.y()) \
                  .arg(i) \
                  .arg((list)[i].x()).arg((list)[i].y()); \
            QTest::qFail(qPrintable(msg), __FILE__, __LINE__); \
        } \
    } \
} while (0)

// add necessary includes here
#include "game.h"

class test_Game : public QObject
{
    Q_OBJECT

public:
    test_Game();
    ~test_Game();

private slots:
    void getBoardDimensions_shouldReturnInitialGridCoordinates_whenCalledAfterConstructor();

    void getSnakeHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor();
    void getSnakeBodyPositions_shouldReturnOneElement_whenCalledAfterConstructor();

    void getFoodPosition_shouldReturnPositionNotColidingWithSnake_whenCalled();
};

test_Game::test_Game() {}

test_Game::~test_Game() {}

void test_Game::getBoardDimensions_shouldReturnInitialGridCoordinates_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);
    QRect expected(0, 0, 20, 20);

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Game::getSnakeHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);
    QPoint expected(10, 10);

    // ACT
    QPoint actual = sut.getSnakeHeadPosition();

    // ASSERT
    QCOMPARE(actual, expected);
}

void test_Game::getSnakeBodyPositions_shouldReturnOneElement_whenCalledAfterConstructor() {
    // ARRANGE
    Game sut(20, 20);

    // ACT
    QList<QPoint> actual = sut.getSnakeBodyPositions();

    // ASSERT
    QCOMPARE(actual.count(), 1);
}

void test_Game::getFoodPosition_shouldReturnPositionNotColidingWithSnake_whenCalled() {
    // ARRANGE
    Game sut(20, 20);

    // ACT
    QPoint actual = sut.getFoodPosition();

    // ASSERT
    QList<QPoint> snake = sut.getSnakeBodyPositions();
    snake << sut.getSnakeHeadPosition();

    QVERIFY_LIST_NOT_INCLUDES_POINT(snake, actual);
}

QTEST_APPLESS_MAIN(test_Game)

#include "test_game.moc"

#include <QTest>

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

QTEST_APPLESS_MAIN(test_Game)

#include "test_game.moc"

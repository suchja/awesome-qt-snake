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
    auto game_dependency = std::make_unique<Game>(20, 20);
    QRect expected(0, 0, 400, 400);

    GameViewModel sut(std::move(game_dependency));

    // ACT
    QRect actual = sut.getBoardDimensions();

    // ASSERT
    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(test_GameViewModel)

#include "test_gameviewmodel.moc"

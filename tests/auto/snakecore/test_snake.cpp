#include <QTest>

// add necessary includes here
#include "snake.h"

class test_Snake : public QObject
{
    Q_OBJECT

public:
    test_Snake();
    ~test_Snake();

private slots:
    void getHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor();
};

test_Snake::test_Snake() {}

test_Snake::~test_Snake() {}

void test_Snake::getHeadPosition_shouldReturnCenterOfBoard_whenCalledAfterConstructor() {
    // ARRANGE
    Snake sut(20, 20, this);
    QPoint expected(10, 10);

    // ACT
    QPoint actual = sut.getHeadPosition();

    // ASSERT
    QCOMPARE(actual, expected);
}

QTEST_APPLESS_MAIN(test_Snake)

#include "test_snake.moc"

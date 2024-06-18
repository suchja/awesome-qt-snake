#include <QTest>

// TODO: js, this should go into some kind of test helper!
#define QVERIFY_POINTS_NOT_EQUAL(actual, expected) \
do { \
        if ((actual) == (expected)) { \
            QString msg = QString("Expected different points but got: (%1, %2) and (%3, %4)") \
                  .arg((actual).x()).arg((actual).y()) \
                  .arg((expected).x()).arg((expected).y()); \
            QTest::qFail(qPrintable(msg), __FILE__, __LINE__); \
    } \
} while (0)

#define QVERIFY_POINTS_ALL_NOT_EQUAL(list) \
do { \
    bool allUnique = true; \
    for (int i = 0; i < (list).size(); ++i) { \
        for (int j = i + 1; j < (list).size(); ++j) { \
            if ((list)[i] == (list)[j]) { \
                QString msg = QString("Duplicate found: (%1, %2) at positions %3 and %4") \
                      .arg((list)[i].x()).arg((list)[i].y()) \
                      .arg(i).arg(j); \
                QTest::qFail(qPrintable(msg), __FILE__, __LINE__); \
            } \
            else { \
                allUnique = false; \
            } \
        } \
    } \
    QVERIFY2(!allUnique, "All points are unique"); \
} while (0)

// add necessary includes here
#include "foodgenerator.h"

class test_FoodGenerator : public QObject
{
    Q_OBJECT

public:
    test_FoodGenerator();
    ~test_FoodGenerator();

private slots:
    void getFoodOnRandomPosition_shouldReturnPositionWithinBoardDimension_whenCalled();

    void getFoodOnRandomPosition_shouldReturnRandomPosition_whenCalledAfterConstructor();
    void getFoodOnRandomPosition_shouldReturnRandomPosition_whenCalledOften();
};

test_FoodGenerator::test_FoodGenerator() {}

test_FoodGenerator::~test_FoodGenerator() {}

void test_FoodGenerator::getFoodOnRandomPosition_shouldReturnPositionWithinBoardDimension_whenCalled() {
    // ARRANGE
    FoodGenerator sut(20, 20);

    // ACT
    QPoint actual = sut.getFoodOnRandomPosition();

    // ASSERT
    QVERIFY2(actual.x() >= 0 && actual.x() <= 20,
             qPrintable(QString("x-Value %1 is not within range [%2, %3]").arg(actual.x()).arg(0).arg(20)));

    QVERIFY2(actual.y() >= 0 && actual.y() <= 20,
             qPrintable(QString("y-Value %1 is not within range [%2, %3]").arg(actual.y()).arg(0).arg(20)));
}

void test_FoodGenerator::getFoodOnRandomPosition_shouldReturnRandomPosition_whenCalledAfterConstructor() {
    QSKIP("Testing output of random generator might lead to wrongly failing tests. AntiPattern", SkipAll);

    // ARRANGE
    FoodGenerator firstSut(20, 20);
    FoodGenerator secondSut(20, 20);

    // ACT
    QPoint firstIteration = firstSut.getFoodOnRandomPosition();
    QPoint secondIteration = secondSut.getFoodOnRandomPosition();

    // ASSERT
    QVERIFY_POINTS_NOT_EQUAL(firstIteration, secondIteration);
}

void test_FoodGenerator::getFoodOnRandomPosition_shouldReturnRandomPosition_whenCalledOften() {
    QSKIP("Testing output of random generator might lead to wrongly failing tests. AntiPattern", SkipAll);

    // ARRANGE
    FoodGenerator sut(20, 20);
    QList<QPoint> actual_positions;

    // ACT
    for (int i = 0; i < 30; ++i) {
        actual_positions << sut.getFoodOnRandomPosition();
    }

    // ASSERT
    QVERIFY_POINTS_ALL_NOT_EQUAL(actual_positions);
}

QTEST_APPLESS_MAIN(test_FoodGenerator)

#include "test_foodgenerator.moc"

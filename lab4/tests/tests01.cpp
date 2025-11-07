#include <gtest/gtest.h>
#include <memory>

#include "array.h"
#include "figure.h"
#include "point.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "pentagon.h"

using namespace std;

using std::make_shared;
using std::shared_ptr;

template <Scalar T>
shared_ptr<Rhombus<T>> makeRhombus() {
    return make_shared<Rhombus<T>>(
        Point<T>(0, 0), Point<T>(2, 1), Point<T>(0, 2), Point<T>(-2, 1)
    );
}

template <Scalar T>
shared_ptr<Trapezoid<T>> makeTrapezoid() {
    return make_shared<Trapezoid<T>>(
        Point<T>(-2, 0), Point<T>(2, 0), Point<T>(1, 2), Point<T>(-1, 2)
    );
}

template <Scalar T>
shared_ptr<Pentagon<T>> makePentagon() {
    return make_shared<Pentagon<T>>(
        Point<T>(0, 0), Point<T>(2, 0), Point<T>(2, 2), Point<T>(1, 3), Point<T>(0, 2)
    );
}



TEST(ArrayTest, AddAndGetFigures) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(trapezoid);

    EXPECT_EQ(array.getSize(), 3);
    EXPECT_EQ(array.getFigure(0), rhombus);
    EXPECT_EQ(array.getFigure(1), pentagon);
    EXPECT_EQ(array.getFigure(2), trapezoid);

    EXPECT_EQ(array[0], rhombus);
    EXPECT_EQ(array[1], pentagon);
    EXPECT_EQ(array[2], trapezoid);
}

TEST(ArrayTest, TotalArea) {
    Array<double> array;
    auto rhombus = makeRhombus<double>();    
    auto pentagon = makePentagon<double>(); 
    auto trapezoid = makeTrapezoid<double>(); 

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    array.addFigure(trapezoid);

    double expected_area = 15.0;
    EXPECT_DOUBLE_EQ(array.getAllArea(), expected_area);
}

TEST(ArrayTest, RemoveFigure) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(rhombus);    
    array.addFigure(pentagon);  
    array.addFigure(trapezoid);  

    array.removeFigure(1);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getFigure(0), rhombus);
    EXPECT_EQ(array.getFigure(1), trapezoid);

    array.removeFigure(0); 
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_EQ(array.getFigure(0), trapezoid);

    array.removeFigure(0); 
    EXPECT_EQ(array.getSize(), 0);

    EXPECT_NO_THROW(array.removeFigure(0));
    EXPECT_EQ(array.getSize(), 0);
}

TEST(ArrayTest, CopyArray) {
    Array<int> array1;
    auto rhombus = makeRhombus<int>();
    array1.addFigure(rhombus);

    Array<int> array2 = array1;
    EXPECT_EQ(array2.getSize(), array1.getSize());

    EXPECT_NE(array2.getFigure(0), array1.getFigure(0));

    EXPECT_EQ(static_cast<double>(*array2.getFigure(0)), static_cast<double>(*array1.getFigure(0)));
}

TEST(ArrayTest, MoveArray) {
    Array<int> array1;
    auto rhombus = makeRhombus<int>();
    array1.addFigure(rhombus);
    auto original_ptr = array1.getFigure(0);

    Array<int> array2 = move(array1); 
    
    EXPECT_EQ(array2.getSize(), 1);
    EXPECT_EQ(array2.getFigure(0), original_ptr);

    EXPECT_EQ(array1.getSize(), 0);
}

TEST(ArrayTest, ResizeArray) {
    Array<int> array(2);
    EXPECT_EQ(array.getCapacity(), 2);

    auto rhombus = makeRhombus<int>();
    auto pentagon = makePentagon<int>();
    auto trapezoid = makeTrapezoid<int>();

    array.addFigure(rhombus);
    array.addFigure(pentagon);
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_EQ(array.getCapacity(), 2); 

    array.addFigure(trapezoid);
    EXPECT_EQ(array.getSize(), 3);
    EXPECT_GE(array.getCapacity(), 3);
}

TEST(ArrayTest, IndexOutOfBounds) {
    Array<int> array;
    auto rhombus = makeRhombus<int>();
    array.addFigure(rhombus); 

    EXPECT_EQ(array.getFigure(10), nullptr); 
    EXPECT_EQ(array[10], nullptr);
}
#include <iostream>
#include <memory>
#include <vector>

#include "array.h"
#include "figure.h"
#include "point.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "pentagon.h"

using namespace std;

int main() {
    using T = double;

    cout << "--- Демонстрация создания фигур ---" << endl;


    auto rhombus = make_shared<Rhombus<T>>(
        Point<T>(0, 0), Point<T>(2, 1), Point<T>(0, 2), Point<T>(-2, 1)
    );

    auto trapezoid = make_shared<Trapezoid<T>>(
        Point<T>(-2, 0), Point<T>(2, 0), Point<T>(1, 1.732), Point<T>(-1, 1.732)
    );

    auto pentagon = make_shared<Pentagon<T>>(
        Point<T>(0, 2), Point<T>(1.9, 0.6), Point<T>(1.2, -1.6),
        Point<T>(-1.2, -1.6), Point<T>(-1.9, 0.6)
    );

    cout << "--- Демонстрация Array<T> ---" << endl;

    Array<T> arr;
    arr.addFigure(rhombus);
    arr.addFigure(trapezoid);
    arr.addFigure(pentagon);

    cout << "Все фигуры в 'arr':" << endl;
    arr.printFigures();

    cout << "\nОбщая площадь: " << arr.getAllArea() << endl;

    cout << "\n--- Демонстрация удаления (индекс 1) ---" << endl;
    arr.removeFigure(1); 

    cout << "Оставшиеся фигуры:" << endl;
    arr.printFigures();
    cout << "Новая общая площадь: " << arr.getAllArea() << endl;

    arr.addFigure(trapezoid); 

    cout << "\n--- Демонстрация конструктора копирования ---" << endl;
    Array<T> arr_copy = arr;
    cout << "Фигуры в 'arr_copy':" << endl;
    arr_copy.printFigures();

    cout << "\n--- Демонстрация конструктора перемещения ---" << endl;
    Array<T> arr_moved = move(arr_copy);
    cout << "Фигуры в 'arr_moved':" << endl;
    arr_moved.printFigures();

    cout << "\nРазмер 'arr_copy' после перемещения: " << arr_copy.getSize() << endl;

    cout << "\n--- Демонстрация приведения к double ---" << endl;
    double first_figure_area = static_cast<double>(*arr_moved[0]);
    cout << "Площадь первой фигуры (arr_moved[0]): " << first_figure_area << endl;

    return 0;
}
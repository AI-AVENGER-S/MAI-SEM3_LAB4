#pragma once
#include <type_traits>
#include <concepts>
#include <iostream>
#include <cmath>


using namespace std;

template<typename T>
concept Scalar = is_arithmetic_v<T>;

template<Scalar T>
struct Point {
    T x{0};
    T y{0};

    Point() = default;
    Point(T x_, T y_) : x(x_), y(y_) {}

    Point(const Point& other) = default;
    Point(Point&& other) noexcept = default;
    Point& operator=(const Point& other) = default;
    Point& operator=(Point&& other) noexcept = default;

    bool operator==(const Point& o) const {
        constexpr double EPS = 1e-9;
        return abs(static_cast<double>(x) - static_cast<double>(o.x)) < EPS
            && abs(static_cast<double>(y) - static_cast<double>(o.y)) < EPS;
    }
};

template<Scalar T>
ostream& operator<<(ostream& os, const Point<T>& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

template<Scalar T>
istream& operator>>(istream& is, Point<T>& p) {
    is >> p.x >> p.y;
    return is;
}

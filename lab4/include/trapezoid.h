#pragma once

#include <optional>
#include <cmath>
#include <stdexcept>
#include <memory>

#include "figure.h"
#include "point.h"

using namespace std;

template <typename T>
optional<pair<Point<T>, double>> circumcircle(const Point<T>& A, const Point<T>& B, const Point<T>& C) {
    double x1 = static_cast<double>(A.x), y1 = static_cast<double>(A.y);
    double x2 = static_cast<double>(B.x), y2 = static_cast<double>(B.y);
    double x3 = static_cast<double>(C.x), y3 = static_cast<double>(C.y);

    double a = x1 - x2, b = y1 - y2;
    double c = x1 - x3, d = y1 - y3;
    double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
    double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
    double det = a * d - b * c;
    if (abs(det) < 1e-12) return nullopt;

    double cx = (d * e - b * f) / det;
    double cy = (-c * e + a * f) / det;
    double r = hypot(cx - x1, cy - y1);
    Point<T> center{static_cast<T>(cx), static_cast<T>(cy)};
    return make_pair(center, r);
}

template <Scalar T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() {
        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);
    }

    Trapezoid(const Point<T>& p1, const Point<T>& p2,
        const Point<T>& p3, const Point<T>& p4) {

        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);

        this->points_[0] = p1;
        this->points_[1] = p2;
        this->points_[2] = p3;
        this->points_[3] = p4;
    }


    Trapezoid(const Trapezoid& other) {
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
    }

    Trapezoid& operator=(const Trapezoid& other) {
        if (this == &other) return *this;
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
        return *this;
    }

    Trapezoid(Trapezoid&& other) noexcept {
        this->size_ = other.size_;
        this->points_ = move(other.points_);
        other.size_ = 0;
    }

    Trapezoid& operator=(Trapezoid&& other) noexcept {
        if (this == &other) return *this;
        this->size_ = other.size_;
        this->points_ = move(other.points_);
        other.size_ = 0;
        return *this;
    }

    ~Trapezoid() = default;

    void read(istream& is) override {
        cout << "Введите 4 точки трапеции (x y): " << endl;
        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);
        for (size_t i = 0; i < this->size_; ++i) {
            is >> this->points_[i];
        }

        auto circ = circumcircle(this->points_[0], this->points_[1], this->points_[2]);
        if (!circ.has_value()) {
            throw runtime_error("Это не трапеция");
        }
        auto [center, r] = circ.value();
        double eps = 1e-6;
        double d = hypot(static_cast<double>(this->points_[3].x - center.x), static_cast<double>(this->points_[3].y - center.y));
        if (abs(d - r) > eps) {
            throw runtime_error("Четвертая точка не вписана в окружность");
        }
    }

    void print(ostream& os) const override {
        os << "Трапеция: ";
        for (size_t i = 0; i < this->size_; ++i) {
            os << this->points_[i] << " ";
        }
    }

    Point<T> getCenter() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < this->size_; ++i) {
            cx += this->points_[i].x;
            cy += this->points_[i].y;
        }
        return Point<T>(cx / this->size_, cy / this->size_);
    }

    double getArea() const override {
        double area = 0.0;
        for (size_t i = 0; i < this->size_; ++i) {
            Point<T>& p1 = this->points_[i];
            Point<T>& p2 = this->points_[(i + 1) % this->size_]; 
            area += (static_cast<double>(p1.x) * static_cast<double>(p2.y) - 
                     static_cast<double>(p2.x) * static_cast<double>(p1.y));
        }
        return abs(area) / 2.0;
    }

    operator double() const override {
        return getArea();
    }

    unique_ptr<Figure<T>> clone() const override {
        return make_unique<Trapezoid<T>>(*this);
    }

    bool operator==(const Figure<T>& other) const override {
        const Trapezoid<T>* trapezoid = dynamic_cast<const Trapezoid<T>*>(&other);
        if (!trapezoid) {
            return false;
        }
        for (size_t i = 0; i < this->size_; ++i) {
            if (!(this->points_[i] == trapezoid->points_[i])) {
                return false;
            }
        }
        return true;
    }
};
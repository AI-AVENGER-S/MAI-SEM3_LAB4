#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "figure.h"

using namespace std;

template <Scalar T>
class Rhombus : public Figure<T> {
private:
    static T distance(const Point<T>& a, const Point<T>& b) {
        T dx = a.x - b.x;
        T dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }

public:
    Rhombus() {
        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);
    }
    Rhombus(const Point<T>& p1, const Point<T>& p2,
        const Point<T>& p3, const Point<T>& p4) {

        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);

        this->points_[0] = p1;
        this->points_[1] = p2;
        this->points_[2] = p3;
        this->points_[3] = p4;
    }

    Rhombus(const Rhombus& other) {
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
    }

    Rhombus& operator=(const Rhombus& other) {
        if (this == &other) {
            return *this;
        }
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
        return *this;
    }

    Rhombus(Rhombus&& other) noexcept {
        this->size_ = other.size_;
        this->points_ = move(other.points_); 
        other.size_ = 0;
    }

    Rhombus& operator=(Rhombus&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        this->size_ = other.size_;
        this->points_ = move(other.points_);
        other.size_ = 0;
        return *this;
    }

    ~Rhombus() = default;

    Point<T> getCenter() const override {
        T cx = 0, cy = 0;
        for (size_t i = 0; i < this->size_; ++i) {
            cx += this->points_[i].x;
            cy += this->points_[i].y;
        }
        return Point<T>(cx / this->size_, cy / this->size_);
    }

    double getArea() const override {
        T d1 = distance(this->points_[0], this->points_[2]);
        T d2 = distance(this->points_[1], this->points_[3]);
        return static_cast<double>(d1 * d2) / 2.0;
    }

    operator double() const override {
        return getArea();
    }

    void print(ostream& os) const override {
        os << "Ромб: ";
        for (size_t i = 0; i < this->size_; ++i) {
            os << this->points_[i] << " ";
        }
    }

    void read(istream& is) override {
        cout << "Введите 4 точки ромба (x y): " << endl;
        this->size_ = 4;
        this->points_ = make_unique<Point<T>[]>(4);
        for (size_t i = 0; i < this->size_; ++i) {
            is >> this->points_[i];
        }
    }

    bool operator==(const Figure<T>& other) const override {
        const Rhombus<T>* rhombus = dynamic_cast<const Rhombus<T>*>(&other);
        if (!rhombus) {
            return false;
        }
        for (size_t i = 0; i < this->size_; ++i) {
            if (!(this->points_[i] == rhombus->points_[i])) {
                return false;
            }
        }
        return true;
    }

    unique_ptr<Figure<T>> clone() const override {
        return make_unique<Rhombus<T>>(*this);
    }
};
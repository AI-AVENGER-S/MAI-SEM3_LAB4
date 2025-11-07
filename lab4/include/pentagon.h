#pragma once

#include <cmath>
#include <iostream>
#include <memory>

#include "figure.h"

using namespace std;

template <Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() {
        this->size_ = 5;
        this->points_ = make_unique<Point<T>[]>(5);
    }
    
    Pentagon(const Point<T>& point1, const Point<T>& point2,
            const Point<T>& point3, const Point<T>& point4,
            const Point<T>& point5) {
        this->size_ = 5;
        this->points_ = make_unique<Point<T>[]>(5);

        this->points_[0] = point1;
        this->points_[1] = point2;
        this->points_[2] = point3;
        this->points_[3] = point4;
        this->points_[4] = point5;
    }

    Pentagon(const Pentagon& other) {
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
    }

    Pentagon& operator=(const Pentagon& other) {
        if (this == &other) return *this;
        this->size_ = other.size_;
        this->points_ = make_unique<Point<T>[]>(this->size_);
        for (size_t i = 0; i < this->size_; ++i) {
            this->points_[i] = other.points_[i];
        }
        return *this;
    }

    Pentagon(Pentagon&& other) noexcept {
        this->size_ = other.size_;
        this->points_ = move(other.points_);
        other.size_ = 0;
    }

    Pentagon& operator=(Pentagon&& other) noexcept {
        if (this == &other) return *this;
        this->size_ = other.size_;
        this->points_ = move(other.points_);
        other.size_ = 0;
        return *this;
    }

    ~Pentagon() = default;

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

    void print(ostream& os) const override {
        os << "5-ти угольник: ";
        for (size_t i = 0; i < this->size_; ++i) {
            os << this->points_[i] << " ";
        }
    }

    void read(istream& is) override {
        cout << "Введите 5 точек пятиугольника (x y): " << endl;
        this->size_ = 5;
        this->points_ = make_unique<Point<T>[]>(5);
        for (size_t i = 0; i < this->size_; ++i) {
            is >> this->points_[i];
        }
    }

    bool operator==(const Figure<T>& other) const override {
        const Pentagon<T>* pentagon = dynamic_cast<const Pentagon<T>*>(&other);
        if (!pentagon) {
            return false;
        }
        for (size_t i = 0; i < this->size_; ++i) {
            if (!(this->points_[i] == pentagon->points_[i])) {
                return false;
            }
        }
        return true;
    }

    unique_ptr<Figure<T>> clone() const override {
        return make_unique<Pentagon<T>>(*this);
    }
};
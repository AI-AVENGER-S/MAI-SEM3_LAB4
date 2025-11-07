#pragma once

#include "point.h" 
#include <memory>
#include <iostream>
#include <cmath>
#include <type_traits> 
#include <concepts>    
#include <utility>     


using namespace std;

template <Scalar T>
class Figure {
protected:
    unique_ptr<Point<T>[]> points_;
    size_t size_ = 0;

public:

    Figure() = default;

    virtual ~Figure() = default;

    Figure(const Figure& other) {
        size_ = other.size_;
        if (size_ > 0) {
            points_ = make_unique<Point<T>[]>(size_);
            for (size_t i = 0; i < size_; ++i) {
                points_[i] = other.points_[i];
            }
        }
    }

    Figure& operator=(const Figure& other) {
        if (this == &other) {
            return *this;
        }
        size_ = other.size_;
        if (size_ > 0) {
            points_ = make_unique<Point<T>[]>(size_);
            for (size_t i = 0; i < size_; ++i) {
                points_[i] = other.points_[i];
            }
        } else {
            points_.reset();
        }
        return *this;
    }

    Figure(Figure&& other) noexcept
        : points_(move(other.points_)), size_(other.size_) {
        other.size_ = 0;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        points_ = move(other.points_);
        size_ = other.size_;
        other.size_ = 0;
        return *this;
    }


    virtual double getArea() const = 0;
    virtual Point<T> getCenter() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual void read(istream& is) = 0;
    virtual bool operator==(const Figure<T>& other) const = 0;
    virtual unique_ptr<Figure<T>> clone() const = 0;


    virtual operator double() const {
        return getArea();
    }

    size_t getSize() const {
        return size_;
    }

    const Point<T>* getPoints() const {
        return points_.get();
    }

    double polygonArea() const {
        if (size_ < 3) return 0.0;
        double a = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            const auto& p1 = points_[i];
            const auto& p2 = points_[(i + 1) % size_];
            a += (static_cast<double>(p1.x) * static_cast<double>(p2.y) -
                  static_cast<double>(p2.x) * static_cast<double>(p1.y));
        }
        return abs(a) / 2.0;
    }

    friend ostream& operator<<(ostream& os, const Figure<T>& f) {
        f.print(os);
        return os;
    }

    friend istream& operator>>(istream& is, Figure<T>& f) {
        f.read(is);
        return is;
    }
};
#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include "figure.h"


using namespace std;

template <Scalar T>
class Array {
private:
    shared_ptr<Figure<T>>* figures_; 
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        auto* new_data = new shared_ptr<Figure<T>>[new_capacity];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = move(figures_[i]);
        delete[] figures_;
        figures_ = new_data;
        capacity_ = new_capacity;
    }

public:
    Array(size_t capacity = 2)
        : figures_(new shared_ptr<Figure<T>>[capacity]),
          size_(0),
          capacity_(capacity) {}

    ~Array() {
        delete[] figures_;
    }

    Array(const Array& other)
        : figures_(new shared_ptr<Figure<T>>[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_) {
        for (size_t i = 0; i < size_; ++i) {
            if (other.figures_[i])
                figures_[i] = shared_ptr<Figure<T>>(other.figures_[i]->clone().release());
            else
                figures_[i] = nullptr;
        }
    }

    Array(Array&& other) noexcept
        : figures_(other.figures_),
          size_(other.size_),
          capacity_(other.capacity_) {
        other.figures_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Array& operator=(Array other) noexcept {
        swap(figures_, other.figures_);
        swap(size_, other.size_);
        swap(capacity_, other.capacity_);
        return *this;
    }

    void addFigure(const shared_ptr<Figure<T>>& figure) {
        if (size_ >= capacity_)
            resize(capacity_ * 2);
        figures_[size_++] = figure;
    }

    void removeFigure(size_t index) {
        if (index >= size_) return;
        for (size_t i = index; i < size_ - 1; ++i)
            figures_[i] = move(figures_[i + 1]);
        --size_;
    }

    shared_ptr<Figure<T>> getFigure(size_t index) const {
        if (index >= size_) return nullptr;
        return figures_[index];
    }

    size_t getSize() const { return size_; }
    size_t getCapacity() const { return capacity_; }

    double getAllArea() const {
        double total = 0.0;
        for (size_t i = 0; i < size_; ++i)
            if (figures_[i])
                total += static_cast<double>(*figures_[i]);
        return total;
    }

    void printFigures() const {
        for (size_t i = 0; i < size_; ++i) {
            cout << "Фигура " << i << ": ";
            if (figures_[i]) {
                figures_[i]->print(cout);
                auto center = figures_[i]->getCenter();
                cout << " | Центр: " << center
                          << " | Площадь: " << static_cast<double>(*figures_[i]);
            } else {
                cout << "(пусто)";
            }
            cout << '\n';
        }
    }

    shared_ptr<Figure<T>> operator[](size_t index) const {
        return getFigure(index);
    }
};

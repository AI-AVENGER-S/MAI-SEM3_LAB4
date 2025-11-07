#pragma once
#include "figure.h"
#include <vector>
#include <memory>
#include <iostream>

template<Scalar T>
class Array {
private:
    std::vector<std::shared_ptr<Figure<T>>> data_;
public:
    Array() = default;
    explicit Array(size_t reserve_capacity) { data_.reserve(reserve_capacity); }

    // copy
    Array(const Array& other) {
        data_.reserve(other.data_.size());
        for (const auto& sp : other.data_) {
            if (sp) data_.push_back(std::shared_ptr<Figure<T>>(sp->clone().release()));
            else data_.push_back(nullptr);
        }
    }
    Array& operator=(const Array& other) {
        if (this != &other) {
            data_.clear();
            data_.reserve(other.data_.size());
            for (const auto& sp : other.data_) {
                if (sp) data_.push_back(std::shared_ptr<Figure<T>>(sp->clone().release()));
                else data_.push_back(nullptr);
            }
        }
        return *this;
    }

    // move
    Array(Array&&) noexcept = default;
    Array& operator=(Array&&) noexcept = default;

    void addFigure(const std::shared_ptr<Figure<T>>& f) {
        data_.push_back(f);
    }

    void removeFigure(size_t index) {
        if (index >= data_.size()) return;
        data_.erase(data_.begin() + static_cast<long>(index));
    }

    std::shared_ptr<Figure<T>> getFigure(size_t index) const {
        if (index >= data_.size()) return nullptr;
        return data_[index];
    }

    size_t getSize() const { return data_.size(); }
    size_t getCapacity() const { return data_.capacity(); }

    double getAllArea() const {
        double sum = 0.0;
        for (const auto& sp : data_) {
            if (sp) sum += static_cast<double>(*sp);
        }
        return sum;
    }

    void printFigures() const {
        for (size_t i = 0; i < data_.size(); ++i) {
            std::cout << "Figure " << i << ": ";
            if (data_[i]) {
                data_[i]->print(std::cout);
                auto center = data_[i]->getCenter();
                std::cout << " | Center: " << center << " | Area: " << static_cast<double>(*data_[i]);
            } else {
                std::cout << "(null)";
            }
            std::cout << "\n";
        }
    }

    std::shared_ptr<Figure<T>> operator[](size_t idx) const {
        return getFigure(idx);
    }
};

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <initializer_list>
#include <ostream>

class Vector {
public:
    // constructors
    Vector();
    explicit Vector(std::size_t size);
    Vector(std::size_t size, double value);
    Vector(std::initializer_list<double> values);

    // rule of five
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    ~Vector();

    // element access
    double& operator[](std::size_t index);
    const double& operator[](std::size_t index) const;

    double& at(std::size_t index);
    const double& at(std::size_t index) const;

    // size information
    std::size_t size() const;
    bool empty() const;

    // modification
    void push_back(double value);
    void clear();

private:
    double* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reserve(std::size_t new_capacity);
};

std::ostream& operator<<(std::ostream& os, const Vector& v);

#endif
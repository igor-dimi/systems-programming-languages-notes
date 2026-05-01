#include <study/vector.hpp>

#include <algorithm>
#include <stdexcept>
#include <utility>

Vector::Vector()
    : data_(nullptr),
      size_(0),
      capacity_(0)
{
}

Vector::Vector(std::size_t size)
    : data_(new double[size]{}),
      size_(size),
      capacity_(size)
{
}

Vector::Vector(std::size_t size, double value)
    : data_(new double[size]),
      size_(size),
      capacity_(size)
{
    std::fill(data_, data_ + size_, value);
}

Vector::Vector(std::initializer_list<double> values)
    : data_(new double[values.size()]),
      size_(values.size()),
      capacity_(values.size())
{
    std::copy(values.begin(), values.end(), data_);
}

Vector::Vector(const Vector& other)
    : data_(new double[other.size_]),
      size_(other.size_),
      capacity_(other.size_)
{
    std::copy(other.data_, other.data_ + size_, data_);
}

Vector& Vector::operator=(const Vector& other)
{
    if (this == &other) {
        return *this;
    }

    double* new_data = new double[other.size_];
    std::copy(other.data_, other.data_ + other.size_, new_data);

    delete[] data_;

    data_ = new_data;
    size_ = other.size_;
    capacity_ = other.size_;

    return *this;
}

Vector::Vector(Vector&& other) noexcept
    : data_(other.data_),
      size_(other.size_),
      capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this == &other) {
        return *this;
    }

    delete[] data_;

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;

    return *this;
}

Vector::~Vector()
{
    delete[] data_;
}

double& Vector::operator[](std::size_t index)
{
    return data_[index];
}

const double& Vector::operator[](std::size_t index) const
{
    return data_[index];
}

double& Vector::at(std::size_t index)
{
    if (index >= size_) {
        throw std::out_of_range("Vector index out of range");
    }

    return data_[index];
}

const double& Vector::at(std::size_t index) const
{
    if (index >= size_) {
        throw std::out_of_range("Vector index out of range");
    }

    return data_[index];
}

std::size_t Vector::size() const
{
    return size_;
}

bool Vector::empty() const
{
    return size_ == 0;
}

void Vector::push_back(double value)
{
    if (size_ == capacity_) {
        std::size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
        reserve(new_capacity);
    }

    data_[size_] = value;
    ++size_;
}

void Vector::clear()
{
    size_ = 0;
}

void Vector::reserve(std::size_t new_capacity)
{
    if (new_capacity <= capacity_) {
        return;
    }

    double* new_data = new double[new_capacity];

    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;

    data_ = new_data;
    capacity_ = new_capacity;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "[";

    for (std::size_t i = 0; i < v.size(); ++i) {
        os << v[i];

        if (i + 1 < v.size()) {
            os << ", ";
        }
    }

    os << "]";
    return os;
}
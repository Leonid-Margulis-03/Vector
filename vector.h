#pragma once

#include <iterator>
#include <cstddef>
#include <algorithm>

class Vector {
public:
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = int;
        using difference_type = ptrdiff_t;
        using pointer = int*;
        using reference = int&;
        Iterator(value_type index, pointer buffer) : buffer_(buffer), index_(index) {
        }
        Iterator() : buffer_(nullptr), index_(0) {
        }
        reference operator*() const {
            return buffer_[index_];
        }
        pointer operator->() {
            return buffer_ + index_;
        }
        // prefix
        Iterator& operator++() {
            index_ += 1;
            return *this;
        }
        // postfix
        Iterator operator++(value_type) {
            Iterator tmp = (*this);
            ++(*this);
            return tmp;
        }
        // prefix
        Iterator& operator--() {
            index_ -= 1;
            return *this;
        }
        // postfix
        Iterator operator--(value_type) {
            Iterator tmp = (*this);
            --(*this);
            return tmp;
        }
        Iterator& operator+=(value_type x) {
            index_ += x;
            return *this;
        }
        Iterator& operator-=(value_type x) {
            index_ -= x;
            return *this;
        }
        Iterator operator+(ptrdiff_t x) const {
            Iterator tmp = (*this);
            tmp.index_ += x;
            return tmp;
        }
        difference_type operator-(const Iterator& other) const {
            return index_ - other.index_;
        }
        difference_type operator+(const Iterator& other) const {
            return index_ + other.index_;
        }
        Iterator operator-(value_type x) const {
            Iterator tmp = (*this);
            tmp.index_ -= x;
            return tmp;
        }
        friend Iterator operator+(value_type k, const Iterator& iterator) {
            Iterator tmp = iterator;
            tmp.index_ += k;
            return tmp;
        }
        // Index Operator
        reference operator[](value_type index2) const {
            return *(buffer_ + index_ + index2);
        }
        // Index Operator
        reference operator[](value_type index2) {
            return *(buffer_ + index_ + index2);
        }

        auto operator<=>(const Iterator& other) const {
            return index_ <=> other.index_;
        }

        bool operator==(const Iterator& other) const {
            return buffer_ == other.buffer_ && index_ == other.index_;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

    private:
        pointer buffer_ = nullptr;
        size_t index_ = 0;
    };
    // Default Constructor
    Vector() {
        this->size_ = 0;
        this->capacity_ = 0;
        this->buffer_ = nullptr;
    }
    // Constructor with zeros
    Vector(size_t size) : size_(size), capacity_(size_) {
        buffer_ = new int[capacity_];
        for (int i = 0; i < static_cast<int>(size_); ++i) {
            *(buffer_ + i) = 0;
        }
    }
    // Constructor with initializer list
    Vector(std::initializer_list<int> list) {
        size_ = list.size();
        capacity_ = list.size();
        buffer_ = new int[capacity_];
        int count = 0;
        for (int x : list) {
            *(buffer_ + count) = x;
            ++count;
        }
    }
    // Copy Constructor
    Vector(const Vector& other)
        : size_(other.size_), capacity_(other.capacity_), buffer_(new int[other.capacity_]) {
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }
    // Move Constructor
    Vector(Vector&& other)
        : size_(other.size_), capacity_(other.capacity_), buffer_(other.buffer_) {
        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    // Copy operator =
    Vector& operator=(const Vector& other) {
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        if (buffer_ != other.buffer_) {
            delete[] buffer_;
            this->buffer_ = new int[capacity_];
        }

        std::copy(other.buffer_, other.buffer_ + other.size_, this->buffer_);
        return *this;
    }
    // Move operator =
    Vector& operator=(Vector&& other) {
        this->size_ = other.size_;
        this->capacity_ = other.capacity_;
        delete[] buffer_;
        this->buffer_ = other.buffer_;

        other.buffer_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }
    // Destructor
    ~Vector() {
        delete[] buffer_;
        buffer_ = nullptr;
    }
    // Swap
    void Swap(Vector& a) {
        Vector tmp = *this;
        *this = a;
        a = tmp;
    }
    // Index Operator
    int operator[](int index) const {
        return *(buffer_ + index);
    }
    // Index Operator
    int& operator[](int index) {
        return *(buffer_ + index);
    }
    // Size
    size_t Size() const {
        return size_;
    }
    // Capacity
    size_t Capacity() const {
        return capacity_;
    }
    // PushBack
    void PushBack(int x) {
        if (size_ >= capacity_) {
            int* buffer2;
            if (capacity_ == 0) {
                buffer2 = new int[1];
                capacity_ = 1;
            } else {
                buffer2 = new int[2 * capacity_];
                capacity_ = 2 * capacity_;
            }
            std::copy(buffer_, buffer_ + size_, buffer2);
            delete[] buffer_;
            buffer_ = buffer2;
        }
        *(buffer_ + size_) = x;
        size_ += 1;
    }
    void PopBack() {
        size_ -= 1;
    }
    void Clear() {
        size_ = 0;
    }
    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            int* buffer2 = new int[new_capacity];
            std::copy(buffer_, buffer_ + size_, buffer2);
            delete[] buffer_;
            buffer_ = buffer2;
            capacity_ = new_capacity;
        }
    }
    Iterator begin() {
        return Iterator(0, buffer_);
    }
    Iterator end() {
        return Iterator(size_, buffer_);
    }

private:
    size_t size_;
    size_t capacity_;
    int* buffer_;
};

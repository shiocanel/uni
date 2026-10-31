#pragma once
#include <cstddef>
#include <utility>
#include <new>
#include <stdexcept>

template <typename T>
class VectorDinamic {
private:
    T* data_{ nullptr };
    std::size_t size_{ 0 };
    std::size_t capacity_{ 0 };

    static T* allocateRaw(std::size_t cap) {
        if (cap == 0) {
            return nullptr;
        }
        return static_cast<T*>(::operator new(sizeof(T) * cap));
    }

    static void destroyRange(T* data, std::size_t count) noexcept {
        if (!data) {
            return;
        }
        for (std::size_t i = 0; i < count; ++i) {
            data[i].~T();
        }
    }

public:
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

    VectorDinamic() = default;

    explicit VectorDinamic(std::size_t initialCapacity) {
        reserve(initialCapacity);
    }

    VectorDinamic(const VectorDinamic& other) {
        reserve(other.size_);
        for (std::size_t i = 0; i < other.size_; ++i) {
            emplace_back(other.data_[i]);
        }
    }

    VectorDinamic(VectorDinamic&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    ~VectorDinamic() {
        clear();
        ::operator delete(data_);
    }

    VectorDinamic& operator=(VectorDinamic other) {
        swap(other);
        return *this;
    }

    void swap(VectorDinamic& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    std::size_t size() const noexcept {
        return size_;
    }

    bool empty() const noexcept {
        return size_ == 0;
    }

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) {
            return;
        }

        T* newData = allocateRaw(newCapacity);
        std::size_t constructed = 0;

        for (; constructed < size_; ++constructed)
            new (newData + constructed) T(std::move_if_noexcept(data_[constructed]));
            
        destroyRange(data_, size_);
        ::operator delete(data_);

        data_ = newData;
        capacity_ = newCapacity;
    }

    void clear() noexcept {
        destroyRange(data_, size_);
        size_ = 0;
    }

    template <typename... Args>
    T& emplace_back(Args&&... args) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }

        new (data_ + size_) T(std::forward<Args>(args)...);
        return data_[size_++];
    }

    void push_back(const T& value) {
        emplace_back(value);
    }

    void push_back(T&& value) {
        emplace_back(std::move(value));
    }

    void erase(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index invalid.");
        }

        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = std::move_if_noexcept(data_[i + 1]);
        }

        data_[size_ - 1].~T();
        --size_;
    }

    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    iterator begin() noexcept {
        return data_;
    }

    iterator end() noexcept {
        return data_ + size_;
    }

    const_iterator begin() const noexcept {
        return data_;
    }

    const_iterator end() const noexcept {
        return data_ + size_;
    }

    const_iterator cbegin() const noexcept {
        return data_;
    }

    const_iterator cend() const noexcept {
        return data_ + size_;
    }
};

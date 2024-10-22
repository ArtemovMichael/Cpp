#pragma once

#include "compressed_pair.h"

#include <cstddef>  // std::nullptr_t

struct Slug {
    template <typename T>
    void operator()(T* ptr) const {
        delete ptr;
    }
};

struct SlugArray {
    template <typename T>
    void operator()(T* ptr) {
        delete[] ptr;
    }
};

// Primary template
template <typename T, typename Deleter = Slug>
class UniquePtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    explicit UniquePtr(T* ptr = nullptr) : data_(ptr, Deleter()) {
    }

    UniquePtr(T* ptr, Deleter deleter) : data_(ptr, std::move(deleter)) {
    }

    UniquePtr(UniquePtr&& other) noexcept {
        Reset(other.Release());
        data_.GetSecond() = std::move(other.data_.GetSecond());
        other.data_.GetFirst() = nullptr;
    }

    template <typename U, typename D>
    UniquePtr(UniquePtr<U, D>&& other) noexcept {
        Reset(other.Release());
        data_.GetSecond() = std::move(other.GetDeleter());
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            Reset(other.data_.GetFirst());
            data_.GetSecond() = std::move(other.data_.GetSecond());
            other.data_.GetFirst() = nullptr;
        }
        return *this;
    }

    template <typename U, typename D>
    UniquePtr& operator=(UniquePtr<U, D>&& other) noexcept {
        if (static_cast<void*>(this) != static_cast<void*>(&other)) {
            Reset(other.Release());
            data_.GetSecond() = std::move(other.GetDeleter());
        }
        return *this;
    }

    UniquePtr& operator=(std::nullptr_t) {
        Reset();
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~UniquePtr() {
        Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release() {
        T* ptr = data_.GetFirst();
        data_.GetFirst() = nullptr;
        return ptr;
    }

    void Reset(T* ptr = nullptr) {
        if (data_.GetFirst() != ptr) {
            T* old_ptr = data_.GetFirst();
            data_.GetFirst() = ptr;
            if (old_ptr != nullptr && old_ptr != this->Get()) {
                data_.GetSecond()(old_ptr);
            }
        }
    }

    void Swap(UniquePtr& other) {
        std::swap(data_, other.data_);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const {
        return data_.GetFirst();
    }

    Deleter& GetDeleter() {
        return data_.GetSecond();
    }

    const Deleter& GetDeleter() const {
        return data_.GetSecond();
    }

    explicit operator bool() const {
        return data_.GetFirst() != nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Single-object dereference operators

    template <typename V = T>
    typename std::enable_if<!std::is_void<V>::value, V&>::type operator*() const {
        return *data_.GetFirst();
    }

    T* operator->() const {
        return data_.GetFirst();
    }

private:
    CompressedPair<T*, Deleter> data_;
};

// Specialization for arrays
template <typename T, typename Deleter>
class UniquePtr<T[], Deleter> {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    explicit UniquePtr(T* ptr = nullptr) : data_(ptr, SlugArray()) {
    }

    UniquePtr(T* ptr, SlugArray deleter) : data_(ptr, std::move(deleter)) {
    }

    UniquePtr(UniquePtr&& other) noexcept {
        Reset(other.Release());
        data_.GetSecond() = std::move(other.data_.GetSecond());
        other.data_.GetFirst() = nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            Reset(other.data_.GetFirst());
            data_.GetSecond() = std::move(other.data_.GetSecond());
            other.data_.GetFirst() = nullptr;
        }
        return *this;
    }

    UniquePtr& operator=(std::nullptr_t) {
        Reset();
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~UniquePtr() {
        Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    T* Release() {
        T* ptr = data_.GetFirst();
        data_.GetFirst() = nullptr;
        return ptr;
    }

    void Reset(T* ptr = nullptr) {
        if (data_.GetFirst() != ptr) {
            T* old_ptr = data_.GetFirst();
            data_.GetFirst() = ptr;
            if (old_ptr != nullptr && old_ptr != this->Get()) {
                data_.GetSecond()(old_ptr);
            }
        }
    }

    void Swap(UniquePtr& other) {
        std::swap(data_, other.data_);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const {
        return data_.GetFirst();
    }

    T& operator[](size_t index) const {
        return data_.GetFirst()[index];
    }

    SlugArray& GetDeleter() {
        return data_.GetSecond();
    }

    const SlugArray& GetDeleter() const {
        return data_.GetSecond();
    }

    explicit operator bool() const {
        return data_.GetFirst() != nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Single-object dereference operators
    T* operator->() const {
        return data_.GetFirst();
    }

private:
    CompressedPair<T*, SlugArray> data_;
};

#pragma once

#include "sw_fwd.h"  // Forward declaration

#include <cstddef>  // std::nullptr_t

struct ControlBlockBase {
    size_t count;

    ControlBlockBase() : count(1) {
    }

    virtual ~ControlBlockBase() = default;
};

template <typename T>
struct ControlBlockWithObject : ControlBlockBase {
    T ptr;

    template <typename... Args>
    ControlBlockWithObject(Args&&... args) : ptr(std::forward<Args>(args)...) {
    }

    ~ControlBlockWithObject() = default;
};

template <typename T>
struct ControlBlockWithPointer : ControlBlockBase {
    T* ptr;

    ControlBlockWithPointer(T* ptr) : ptr(ptr) {
    }

    ~ControlBlockWithPointer() {
        delete ptr;
    }
};

// https://en.cppreference.com/w/cpp/memory/shared_ptr
template <typename T>
class SharedPtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors

    SharedPtr() : SharedPtr(nullptr) {
    }

    SharedPtr(std::nullptr_t) {
        ptr_ = nullptr;
        control_block_ = nullptr;
    }

    explicit SharedPtr(T* ptr) {
        ptr_ = ptr;
        if (ptr) {
            control_block_ = new ControlBlockWithPointer<T>(ptr);
        } else {
            control_block_ = nullptr;
        }
    }

    template <typename U>
    explicit SharedPtr(U* ptr) {
        ptr_ = ptr;
        if (ptr) {
            control_block_ = new ControlBlockWithPointer<U>(ptr);
        } else {
            control_block_ = nullptr;
        }
    }

    SharedPtr(const SharedPtr& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->count;
        }
    }

    template <typename U>
    SharedPtr(const SharedPtr<U>& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->count;
        }
    }

    SharedPtr(SharedPtr&& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        other.ptr_ = nullptr;
        other.control_block_ = nullptr;
    }

    template <typename U>
    SharedPtr(SharedPtr<U>&& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        other.ptr_ = nullptr;
        other.control_block_ = nullptr;
    }

    // Aliasing constructor
    // #8 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    template <typename Y>
    SharedPtr(const SharedPtr<Y>& other, T* ptr) {
        ptr_ = ptr;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->count;
        }
    }

    // Promote `WeakPtr`
    // #11 from https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    explicit SharedPtr(const WeakPtr<T>& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->count;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    SharedPtr& operator=(const SharedPtr& other) {
        if (control_block_ != other.control_block_) {
            Reset();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            if (control_block_) {
                ++control_block_->count;
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) {
        if (control_block_ != other.control_block_) {
            Reset();
            ptr_ = other.ptr_;
            control_block_ = other.control_block_;
            other.ptr_ = nullptr;
            other.control_block_ = nullptr;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~SharedPtr() {
        Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset() {
        Reset(nullptr);
    }

    void Reset(T* ptr) {
        if (control_block_ != nullptr) {
            if (control_block_->count == 1) {
                delete control_block_;
            } else {
                --control_block_->count;
            }
        }
        if (ptr) {
            control_block_ = new ControlBlockWithPointer<T>(ptr);
        } else {
            control_block_ = nullptr;
        }
        ptr_ = ptr;
    }

    template <typename U>
    void Reset(U* ptr) {
        if (control_block_ != nullptr) {
            if (control_block_->count == 1) {
                delete control_block_;
            } else {
                --control_block_->count;
            }
        }
        if (ptr) {
            control_block_ = new ControlBlockWithPointer<U>(ptr);
        } else {
            control_block_ = nullptr;
        }
        ptr_ = ptr;
    }

    void Swap(SharedPtr& other) {
        std::swap(ptr_, other.ptr_);
        std::swap(control_block_, other.control_block_);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    T* Get() const {
        return ptr_;
    }

    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

    size_t UseCount() const {
        if (control_block_) {
            return control_block_->count;
        }
        return 0;
    }

    explicit operator bool() const {
        return ptr_ != nullptr;
    }

private:
    T* ptr_;
    ControlBlockBase* control_block_;

    template <typename Y>
    friend class SharedPtr;

    template <typename U, typename... Atgs>
    friend SharedPtr<U> MakeShared(Atgs&&... args);
};

template <typename T, typename U>
inline bool operator==(const SharedPtr<T>& left, const SharedPtr<U>& right) {
    return left.Get() == right.Get();
}

// Allocate memory only once
template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    SharedPtr<T> ptr;
    ptr.control_block_ = new ControlBlockWithObject<T>(std::forward<Args>(args)...);
    ptr.ptr_ = &static_cast<ControlBlockWithObject<T>*>(ptr.control_block_)->ptr;
    return ptr;
}

// Look for usage examples in tests
template <typename T>
class EnableSharedFromThis {
public:
    SharedPtr<T> SharedFromThis();
    SharedPtr<const T> SharedFromThis() const;

    WeakPtr<T> WeakFromThis() noexcept;
    WeakPtr<const T> WeakFromThis() const noexcept;
};

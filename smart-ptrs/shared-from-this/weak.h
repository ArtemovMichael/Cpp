#pragma once

#include "sw_fwd.h"  // Forward declaration
#include "shared.h"

// https://en.cppreference.com/w/cpp/memory/weak_ptr
template <typename T>
class WeakPtr {
public:
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors

    WeakPtr() {
        ptr_ = nullptr;
        created_from_esft_ = false;
        control_block_ = nullptr;
    }

    WeakPtr(const WeakPtr& other) {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->weak_count;
        }
    }

    template <typename U>
    WeakPtr(const WeakPtr<U>& other) noexcept {
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;
        if (control_block_) {
            ++control_block_->weak_count;
        }
    }

    WeakPtr(WeakPtr&& other) {
        ptr_ = other.ptr_;
        created_from_esft_ = other.created_from_esft_;
        control_block_ = other.control_block_;
        other.ptr_ = nullptr;
        other.control_block_ = nullptr;
        created_from_esft_ = false;
    }

    // Demote `SharedPtr`
    // #2 from https://en.cppreference.com/w/cpp/memory/weak_ptr/weak_ptr
    WeakPtr(const SharedPtr<T>& other, bool created_from_esft = false) {
        ptr_ = other.ptr_;
        created_from_esft_ = created_from_esft;
        control_block_ = other.control_block_;
        if (control_block_ && !created_from_esft_) {
            ++control_block_->weak_count;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // `operator=`-s

    WeakPtr& operator=(const WeakPtr& other) {
        if (control_block_ != other.control_block_) {
            Reset();
            ptr_ = other.ptr_;
            created_from_esft_ = other.created_from_esft_;
            control_block_ = other.control_block_;
            if (control_block_) {
                ++control_block_->weak_count;
            }
        }
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) {
        if (control_block_ != other.control_block_) {
            Reset();
            ptr_ = other.ptr_;
            created_from_esft_ = other.created_from_esft_;
            control_block_ = other.control_block_;
            other.ptr_ = nullptr;
            other.created_from_esft_ = false;
            other.control_block_ = nullptr;
        }
        return *this;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Destructor

    ~WeakPtr() {
        Reset();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Modifiers

    void Reset() {
        if (control_block_ != nullptr && !created_from_esft_) {
            if (control_block_->weak_count == 1) {
                if (control_block_->strong_count == 0) {
                    --control_block_->weak_count;
                    delete control_block_;
                } else {
                    --control_block_->weak_count;
                }
            } else {
                --control_block_->weak_count;
            }
        }

        ptr_ = nullptr;
        created_from_esft_ = false;
        control_block_ = nullptr;
    }

    void Swap(WeakPtr& other) {
        std::swap(ptr_, other.ptr_);
        std::swap(created_from_esft_, other.created_from_esft_);
        std::swap(control_block_, other.control_block_);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // Observers

    size_t UseCount() const {
        if (control_block_) {
            return control_block_->strong_count;
        }
        return 0;
    }

    bool Expired() const {
        return UseCount() == 0;
    }

    SharedPtr<T> Lock() const {
        if (Expired()) {
            return SharedPtr<T>();
        }
        return SharedPtr<T>(*this);
    }

private:
    T* ptr_;
    bool created_from_esft_;
    ControlBlockBase* control_block_;

    template <typename U>
    friend class SharedPtr;

    template <typename U>
    friend class WeakPtr;
};

#pragma once

#include <type_traits>
#include <utility>

// базовый класс для элемента пары
template <typename T, bool = std::is_empty_v<T> && !std::is_final_v<T>>
class CompressedPairElement;

// специализация для пустого и не финального типа
template <typename T>
class CompressedPairElement<T, true> : private T {
public:
    CompressedPairElement() = default;

    CompressedPairElement(const T&) {
    }

    CompressedPairElement(T&&) {
    }

    T& Get() & {
        return *this;
    }

    const T& Get() const& {
        return *this;
    }

    T&& Get() && {
        return std::move(*this);
    }
};

// специализация для непустого или финального типа
template <typename T>
class CompressedPairElement<T, false> {
public:
    CompressedPairElement() = default;

    CompressedPairElement(const T& value) : value_(value) {
    }

    CompressedPairElement(T&& value) : value_(std::move(value)) {
    }

    T& Get() & {
        return value_;
    }

    const T& Get() const& {
        return value_;
    }

    T&& Get() && {
        return std::move(value_);
    }

private:
    T value_{};
};

// базовый класс для пары
template <typename F, typename S, bool = std::is_same_v<F, S>>
class CompressedPair;

// специализация для одинаковых типов
template <typename F, typename S>
class CompressedPair<F, S, true> {
public:
    CompressedPair() = default;

    CompressedPair(const F& value) : first_(value), second_(value) {
    }
    CompressedPair(F&& value) : first_(std::move(value)), second_(std::move(value)) {
    }

    F& GetFirst() & {
        return first_.Get();
    }

    const F& GetFirst() const& {
        return first_.Get();
    }

    F&& GetFirst() && {
        return std::move(first_.Get());
    }

    S& GetSecond() & {
        return second_.Get();
    }

    const S& GetSecond() const& {
        return second_.Get();
    }

    S&& GetSecond() && {
        return std::move(second_.Get());
    }

private:
    CompressedPairElement<F, std::is_empty_v<F> && !std::is_final_v<F>> first_{};
    CompressedPairElement<S, std::is_empty_v<S> && !std::is_final_v<S>> second_{};
};

// специализация для разных типов
template <typename F, typename S>
class CompressedPair<F, S, false>
    : private CompressedPairElement<F, std::is_empty_v<F> && !std::is_final_v<F>>,
      private CompressedPairElement<S, std::is_empty_v<S> && !std::is_final_v<S>> {
public:
    CompressedPair() = default;

    CompressedPair(const F& first, const S& second)
        : CompressedPairElement < F,
    std::is_empty_v<F> && !std::is_final_v < F >> (first), CompressedPairElement < S,
    std::is_empty_v<S> && !std::is_final_v < S >> (second) {
    }

    CompressedPair(F&& first, S&& second)
        : CompressedPairElement < F,
    std::is_empty_v<F> && !std::is_final_v < F >> (std::move(first)), CompressedPairElement < S,
    std::is_empty_v<S> && !std::is_final_v < S >> (std::move(second)) {
    }

    CompressedPair(F& first, S&& second)
        : CompressedPairElement < F,
    std::is_empty_v<F> && !std::is_final_v < F >> (first), CompressedPairElement < S,
    std::is_empty_v<S> && !std::is_final_v < S >> (std::move(second)) {
    }

    CompressedPair(S&& second)
        : CompressedPairElement < F,
    std::is_empty_v<F> && !std::is_final_v < F >> (), CompressedPairElement < S,
    std::is_empty_v<S> && !std::is_final_v < S >> (std::move(second)) {
    }

    F& GetFirst() & {
        return CompressedPairElement < F, std::is_empty_v<F> && !std::is_final_v < F >> ::Get();
    }

    const F& GetFirst() const& {
        return CompressedPairElement < F, std::is_empty_v<F> && !std::is_final_v < F >> ::Get();
    }

    F&& GetFirst() && {
        return std::move(CompressedPairElement < F,
                         std::is_empty_v<F> && !std::is_final_v < F >> ::Get());
    }

    S& GetSecond() & {
        return CompressedPairElement < S, std::is_empty_v<S> && !std::is_final_v < S >> ::Get();
    }

    const S& GetSecond() const& {
        return CompressedPairElement < S, std::is_empty_v<S> && !std::is_final_v < S >> ::Get();
    }

    S&& GetSecond() && {
        return std::move(CompressedPairElement < S,
                         std::is_empty_v<S> && !std::is_final_v < S >> ::Get());
    }
};

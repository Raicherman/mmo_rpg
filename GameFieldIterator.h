#pragma once
#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>
#include "Unit.h"

// Итератор по юнитам поля (обёртка над итератором vector<unique_ptr<Unit>>).
// Const = true -> константная версия. Разыменование даёт Unit&.
template <bool Const>
class GameFieldIteratorT {
public:
    using Storage = std::vector<std::unique_ptr<Unit>>;
    using Inner = std::conditional_t<Const, Storage::const_iterator, Storage::iterator>;

    using iterator_category = std::forward_iterator_tag;
    using value_type        = Unit;
    using difference_type   = std::ptrdiff_t;
    using pointer           = std::conditional_t<Const, const Unit*, Unit*>;
    using reference         = std::conditional_t<Const, const Unit&, Unit&>;

    GameFieldIteratorT() = default;
    explicit GameFieldIteratorT(Inner it) : it_(it) {}

    // iterator -> const_iterator
    template <bool C = Const, typename = std::enable_if_t<C>>
    GameFieldIteratorT(const GameFieldIteratorT<false>& o) : it_(o.base()) {}

    reference operator*()  const { return **it_; }
    pointer   operator->() const { return it_->get(); }

    GameFieldIteratorT& operator++()    { ++it_; return *this; }
    GameFieldIteratorT  operator++(int) { auto t = *this; ++it_; return t; }

    bool operator==(const GameFieldIteratorT& o) const { return it_ == o.it_; }
    bool operator!=(const GameFieldIteratorT& o) const { return it_ != o.it_; }

    Inner base() const { return it_; }

private:
    Inner it_{};
};

using GameFieldIterator      = GameFieldIteratorT<false>;
using ConstGameFieldIterator = GameFieldIteratorT<true>;

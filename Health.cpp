#include "Health.h"
#include <algorithm>
#include <stdexcept>

Health::Health(int value) : Health(value, value) {}

Health::Health(int value, int maxValue) : value_(value), max_(maxValue) {
    if (maxValue <= 0) throw std::invalid_argument("Health: max must be > 0");
    if (value < 0 || value > maxValue) throw std::invalid_argument("Health: value out of range");
}

void Health::decrease(int amount) {
    if (amount < 0) throw std::invalid_argument("Health::decrease: negative amount");
    value_ = std::max(0, value_ - amount);
}

void Health::increase(int amount) {
    if (amount < 0) throw std::invalid_argument("Health::increase: negative amount");
    value_ = std::min(max_, value_ + amount);
}

bool Health::isZero() const { return value_ == 0; }
int  Health::value() const  { return value_; }
int  Health::max() const    { return max_; }

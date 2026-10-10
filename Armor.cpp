#include "Armor.h"
#include <algorithm>
#include <stdexcept>

Armor::Armor(int value) : value_(value) {
    if (value < 0) throw std::invalid_argument("Armor: value must be >= 0");
}

int Armor::reduceDamage(int damage) const { return std::max(0, damage - value_); }
int Armor::value() const { return value_; }

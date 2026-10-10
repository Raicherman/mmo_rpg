#include "Attack.h"
#include "Armor.h"
#include <stdexcept>

Attack::Attack(int value) : value_(value) {
    if (value < 0) throw std::invalid_argument("Attack: value must be >= 0");
}

int Attack::calculateDamage(const Armor& targetArmor) const {
    return targetArmor.reduceDamage(value_);
}
int Attack::value() const { return value_; }

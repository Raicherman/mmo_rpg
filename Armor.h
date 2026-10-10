#pragma once

// Броня: уменьшает входящий урон на свою величину (не ниже 0).
class Armor {
public:
    explicit Armor(int value = 0);
    int reduceDamage(int damage) const;
    int value() const;

private:
    int value_;
};

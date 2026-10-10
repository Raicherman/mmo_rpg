#pragma once
class Armor;

// Атака: базовый урон юнита.
class Attack {
public:
    explicit Attack(int value = 1);
    int calculateDamage(const Armor& targetArmor) const;
    int value() const;

private:
    int value_;
};

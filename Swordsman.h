#pragma once
#include "Infantry.h"

class Swordsman : public Infantry {
public:
    Swordsman(int x, int y)
        : Infantry(Health(100), Armor(5), Attack(15), x, y, 1) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<Swordsman>(*this); }
    UnitType getType() const override { return UnitType::Swordsman; }
    char getSymbol() const override { return 'S'; }
};

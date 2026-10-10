#pragma once
#include "Archer.h"

class LightArcher : public Archer {
public:
    LightArcher(int x, int y)
        : Archer(Health(60), Armor(1), Attack(12), x, y, 5) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<LightArcher>(*this); }
    UnitType getType() const override { return UnitType::LightArcher; }
    char getSymbol() const override { return 'L'; }
};

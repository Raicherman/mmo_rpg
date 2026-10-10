#pragma once
#include "Cavalry.h"

class HorseArcher : public Cavalry {
public:
    HorseArcher(int x, int y)
        : Cavalry(Health(90), Armor(3), Attack(14), x, y, 4) {}

    std::unique_ptr<Unit> clone() const override { return std::make_unique<HorseArcher>(*this); }
    UnitType getType() const override { return UnitType::HorseArcher; }
    char getSymbol() const override { return 'R'; }
};

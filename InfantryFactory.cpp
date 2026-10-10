#include "InfantryFactory.h"
#include "Swordsman.h"
#include "Spearman.h"
#include <stdexcept>

std::unique_ptr<Unit> InfantryFactory::createUnit(UnitType type, int x, int y) const {
    switch (type) {
        case UnitType::Swordsman: return std::make_unique<Swordsman>(x, y);
        case UnitType::Spearman: return std::make_unique<Spearman>(x, y);
        default:
            throw std::invalid_argument("InfantryFactory cannot create " + toString(type));
    }
}

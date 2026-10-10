#include "CavalryFactory.h"
#include "Cataphract.h"
#include "HorseArcher.h"
#include <stdexcept>

std::unique_ptr<Unit> CavalryFactory::createUnit(UnitType type, int x, int y) const {
    switch (type) {
        case UnitType::Cataphract: return std::make_unique<Cataphract>(x, y);
        case UnitType::HorseArcher: return std::make_unique<HorseArcher>(x, y);
        default:
            throw std::invalid_argument("CavalryFactory cannot create " + toString(type));
    }
}

#include "ArcherFactory.h"
#include "LightArcher.h"
#include "HeavyArcher.h"
#include <stdexcept>

std::unique_ptr<Unit> ArcherFactory::createUnit(UnitType type, int x, int y) const {
    switch (type) {
        case UnitType::LightArcher: return std::make_unique<LightArcher>(x, y);
        case UnitType::HeavyArcher: return std::make_unique<HeavyArcher>(x, y);
        default:
            throw std::invalid_argument("ArcherFactory cannot create " + toString(type));
    }
}

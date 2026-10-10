#pragma once
#include <string>

// Перечисление всех конкретных видов юнитов.
enum class UnitType {
    Swordsman, Spearman,        // пехота
    LightArcher, HeavyArcher,   // лучники
    Cataphract, HorseArcher     // конница
};

inline std::string toString(UnitType t) {
    switch (t) {
        case UnitType::Swordsman:   return "Swordsman";
        case UnitType::Spearman:    return "Spearman";
        case UnitType::LightArcher: return "LightArcher";
        case UnitType::HeavyArcher: return "HeavyArcher";
        case UnitType::Cataphract:  return "Cataphract";
        case UnitType::HorseArcher: return "HorseArcher";
    }
    return "Unknown";
}

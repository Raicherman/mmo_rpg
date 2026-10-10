#include <iostream>
#include <memory>
#include "GameField.h"
#include "InfantryFactory.h"
#include "ArcherFactory.h"
#include "CavalryFactory.h"
#ifdef _WIN32
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

static void printUnits(const GameField& f) {
    for (const auto& u : f)
        std::cout << "  " << u.getSymbol() << " " << toString(u.getType())
                  << " (" << u.getX() << "," << u.getY() << ")"
                  << " HP=" << u.getHealth().value() << "/" << u.getHealth().max()
                  << " ARM=" << u.getArmor().value()
                  << " ATK=" << u.getAttack().value() << "\n";
}

static GameField makeField(const InfantryFactory& inf, const ArcherFactory& arc, const CavalryFactory& cav) {
    GameField f(12, 8, 10);
    f.addUnit(inf, UnitType::Swordsman,   1, 1);
    f.addUnit(inf, UnitType::Spearman,    2, 1);
    f.addUnit(arc, UnitType::LightArcher, 3, 3);
    f.addUnit(arc, UnitType::HeavyArcher, 4, 3);
    f.addUnit(cav, UnitType::Cataphract,  6, 5);
    f.addUnit(cav, UnitType::HorseArcher, 8, 6);
    return f;
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
    InfantryFactory inf; ArcherFactory arc; CavalryFactory cav;

    std::cout << "=== Сценарий 1: создание поля и наполнение через фабрики ===\n";
    GameField field = makeField(inf, arc, cav);
    std::cout << field << "Юнитов: " << field.size() << "/" << field.maxUnits() << "\n";
    printUnits(field);

    std::cout << "\nПроверка ошибок:\n";
    try { field.addUnit(inf, UnitType::Swordsman, 100, 100); }
    catch (const std::exception& e) { std::cout << "  вне поля: " << e.what() << "\n"; }
    try { field.addUnit(inf, UnitType::Swordsman, 1, 1); }
    catch (const std::exception& e) { std::cout << "  занято: " << e.what() << "\n"; }
    try { field.addUnit(inf, UnitType::Cataphract, 0, 0); }
    catch (const std::exception& e) { std::cout << "  не та фабрика: " << e.what() << "\n"; }
    GameField tiny(3, 3, 1);
    tiny.addUnit(inf, UnitType::Swordsman, 0, 0);
    try { tiny.addUnit(inf, UnitType::Spearman, 1, 1); }
    catch (const std::exception& e) { std::cout << "  лимит: " << e.what() << "\n"; }

    std::cout << "\n=== Сценарий 2: глубокое копирование ===\n";
    GameField copy = field;                         // конструктор копирования
    copy.getUnit(std::size_t(0)).getHealth().decrease(40);
    copy.moveUnit(1, 1, 1, 0) ;                     // занято Spearman -> false
    copy.moveUnit(6, 5, 2, -1);                     // катафракт в копии едет
    copy.removeUnit(std::size_t(5));
    std::cout << "Оригинал (HP мечника " << field.getUnit(std::size_t(0)).getHealth().value()
              << ", юнитов " << field.size() << "):\n" << field;
    std::cout << "Копия (HP мечника " << copy.getUnit(std::size_t(0)).getHealth().value()
              << ", юнитов " << copy.size() << "):\n" << copy;
    GameField assigned(5, 5, 2);
    assigned = field;                               // оператор присваивания копированием
    std::cout << "После operator=: юнитов " << assigned.size() << ", поле "
              << assigned.width() << "x" << assigned.height() << "\n";

    std::cout << "\n=== Сценарий 3: перемещение, итерация, удаление ===\n";
    GameField moved = std::move(field);             // конструктор перемещения
    std::cout << "Исходное поле после move: empty=" << std::boolalpha << field.empty()
              << ", новое: size=" << moved.size() << "\n";

    for (auto& u : moved) u.getHealth().decrease(30);        // массовое действие
    std::cout << "Всем -30 HP:\n"; printUnits(moved);
    for (auto& u : moved) u.getHealth().increase(10);        // массовое лечение
    std::cout << "Всем +10 HP:\n"; printUnits(moved);

    // Бой: мечник бьёт лёгкого лучника, пока тот не погибнет
    Unit* sword = moved.getUnit(1, 1);
    Unit* light = moved.getUnit(3, 3);
    int hits = 0;
    while (light->isAlive()) { sword->attackUnit(*light); ++hits; }
    std::cout << "\nМечник убил лёгкого лучника за " << hits << " удара(ов)\n";

    // Удаление во время итерации
    for (auto it = moved.begin(); it != moved.end(); ) {
        if (it->getHealth().isZero()) {
            std::cout << "  удаляю " << toString(it->getType()) << "\n";
            it = moved.erase(it);
        } else ++it;
    }
    std::cout << moved << "Осталось юнитов: " << moved.size() << "\n";

    GameField assignedMove(2, 2, 1);
    assignedMove = std::move(moved);                // оператор перемещения
    std::cout << "После move-присваивания: moved.size=" << moved.size()
              << ", assignedMove.size=" << assignedMove.size() << "\n";
    return 0;
}

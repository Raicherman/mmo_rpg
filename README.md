MMO-RPG: поле с юнитами (C++17)

Сборка: cmake -B build && cmake --build build && ./build/mmo_rpg
или g++ -std=c++17 -Wall -Wextra *.cpp -o mmo_rpg.

UnitFactory объявляет фабричный метод createUnit(type, x, y), а InfantryFactory,
ArcherFactory, CavalryFactory решают, какой конкретный класс создать. Набор типов
фиксирован, семейств продуктов («Армия Севера/Юга») нет, поэтому Абстрактная фабрика
избыточна. Клиентский код (GameField, main) зависит только от UnitFactory, и
новый вид юнита добавляется без изменения клиента.

Итератор
GameFieldIteratorT<Const> оборачивает итератор vector<unique_ptr<Unit>>, operator
возвращает Unit. Есть begin()/end() (в т.ч. const), поэтому работает range-for.
GameField::erase(it) возвращает следующий валидный итератор для удаления при обходе.

 Правило пяти
GameField явно реализует деструктор, копирование (глубокое, через Unit::clone()),
copy-and-swap присваивание, перемещение и присваивание перемещением.

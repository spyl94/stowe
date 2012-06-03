#include "room.h"

Room::Room(QString name, int capacity, bool computer)
    :_name(name),_capacity(capacity),_computer(computer)
{}

Amphi::Amphi(QString name, int capacity)
    : Room(name,capacity)
{}

Tp::Tp(QString name, int capacity)
    : Room(name,capacity,true)
{}

Td::Td(QString name, int capacity)
    : Room(name,capacity)
{}

QDebug operator<<(QDebug os, const Room &r){
    os.nospace() << r.dump();
    return os.maybeSpace();
}
QString Amphi::dump() const {
    return "Amphi:"+ _name + ":" + QString::number(_capacity);
}
QString Tp::dump() const {
    return "Tp:"+ _name + ":" + QString::number(_capacity);
}
QString Td::dump() const {
    return "Td:"+ _name + ":" + QString::number(_capacity);
}

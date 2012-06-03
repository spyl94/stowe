#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <QString>
#include <QDebug>

enum RoomType {
    TP, TD, AMPHI
};


class Room
{
protected:
    QString _name;
    int _capacity;
    bool _computer;

public:
    Room(QString name, int capacity, bool computer=false);
    int getCapacity() const {return _capacity;}
    QString getName() const {return _name;}
    virtual RoomType getType() const = 0;
    virtual QString dump() const = 0;
    friend QDebug operator<<(QDebug os, const Room &r);
    virtual ~Room(){}
};

class Amphi : public Room
{

public:
    Amphi(QString, int = 200);
    RoomType getType() const {return AMPHI;}
    QString dump() const;
    virtual ~Amphi(){}

};

class Tp : public Room
{
public:
    Tp(QString name, int capacity = 40);
    RoomType getType() const {return TP;}
    QString dump() const;
    virtual ~Tp(){}
};

class Td : public Room
{
public:
    Td(QString name, int capacity = 40);
    RoomType getType() const {return TD;}
    QString dump() const;
    virtual ~Td(){}
};

#endif // ROOM_H

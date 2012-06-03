#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <Qvector>
#include <QtAlgorithms>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QListData>
#include <QDebug>
#include "user.h"
#include "room.h"
#include "syllabus.h"


class TimeSlot
{
    Lesson* _cour;
    Prof* _prof;
    Room* _room;
    People* _people;
    QDateTime _debut;
    QDateTime _fin;

public:
    TimeSlot(Lesson* cour,Prof* prof,Room* room,People* people,QDateTime debut, QDateTime fin);
    QDateTime getDebut() const {return _debut;}
    QDateTime getFin() const {return _fin;}
    People* getPeople() const {return _people;}
    Room* getRoom() const {return _room;}
    Prof* getProf() const {return _prof;}
    Lesson* getLesson() const {return _cour;}
    friend QDebug operator <<(QDebug os, const TimeSlot &s){
        os << "cour:" << *s._cour << "pour" << *s._people;
        os << s._debut << s._fin << "en" << *s._room << " avec " << *s._prof;
        return os;
    }
};

#endif // TIME_H

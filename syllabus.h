#ifndef SYLLABUS_H
#define SYLLABUS_H

#include <iostream>
#include "room.h"
#include "user.h"
#include <QVector>

class Lesson
{
    int _id;
    int _time; //Minutes
    RoomType _type; //Amphi,TD,TP
    QString _name;

public:
    Lesson(int id,RoomType type,int time, QString name);
    RoomType getType() const {return _type;}
    QString getName() const {return _name;}
    int getTime() const {return _time;}
    friend QDebug operator <<(QDebug os, const Lesson &s){
        os << s._id << s._name <<"durée:" << s._time << "min en";
        switch(s._type){
            case AMPHI: os << "Amphi"; break;
            case TD: os << "TD"; break;
            case TP: os << "TP"; break;
            default: break;
        }
        return os;
    }
};

class Syllabus
{
    QString _name;
    QVector<Lesson*> _lessons;
    QVector<Prof*> _profs;
public:
    Syllabus(QString name);
    void addLesson(Lesson* const& cour);
    void addProf(Prof* const&prof);
    int getLessonsSize() {return _lessons.size();}
    Lesson* getLessonsAt(int i) {return _lessons.at(i);}
    QString getName() {return _name;}
    QVector<Prof*>& getProfs() {return _profs;}

    friend QDebug operator <<(QDebug os, const Syllabus &s){
        os << s._name << ":\n" ;
        for (int i =0; i < s._lessons.size(); i++) os << *s._lessons.at(i) << "\n";
        for (int i =0; i < s._profs.size(); i++) os << *s._profs.at(i) << "\n";
        return os;
    }
};

#endif // SYLLABUS_H

#ifndef STOWE_H
#define STOWE_H


#include "time.h"

class Strategie;


class Stowe
{
    QVector<Prof*> _profs;
    QVector<Room*> _rooms;
    QVector<Promo*> _promos;
    QMap<QString, Syllabus*> _matieres;
    QMap<QString, QStringList> _programme;
    Strategie* _strategie; //Algorithme de génération

    QList<TimeSlot*> _list;
    QList<QDate> _ferie;

private:
    void loadData();
    void setStrategie(Strategie* strategie);

public:
    Stowe();
    void generate();
    void dump();
    QVector<Prof*> const& getProfs() const {return _profs;}
    QVector<Room*> const& getRooms() const {return _rooms;}
    QVector<Promo*> const& getPromos()const{return _promos;}
    QMap<QString, Syllabus*> const& getSyllabus() const {return _matieres;}
    QMap<QString, QStringList> const& getProgramme() const {return _programme;}
    QList<TimeSlot*> const& getTimeList() const {return _list;}

    void delProf(QString name);
    void delProf(int i);
    void delRoom(int i);
    void delSyllabus(QString name);
    void addProf(QString name, QStringList mat);
    void addRoom(QString name, RoomType type, int capacity);
    void addIndispo(QString name,QDateTime debut,QDateTime fin);
    void addSyllabus(QString name, int cm=0, int tp=0, int td=0);
    void addFerie(QDate date);

    void dumpTimeList();

};


class Strategie
{
    const QVector<Prof*>* _profs;
    const QVector<Room*>*  _rooms;
    const QMap<QString, Syllabus*>* _matieres;
    const QList<QDate>* _ferie;

    QList<TimeSlot*>* _list;

private:
    QDateTime getFirstDisponibility(People* people, int duree);
    QDateTime getNextDisponibility(People *people, QDateTime current, int duree);
    QVector<Room*> getRoomsFree(RoomType type, QDateTime current, QDateTime fin);
    bool containPeopleAt(int i, People* people);

public:
    Strategie(QVector<Prof*> const& profs, QVector<Room*> const& rooms, QMap<QString, Syllabus*> const &matiere,
              QList<TimeSlot*> & list, QList<QDate> const& ferie);
    bool addTimeSlot(QVector<Prof*> const& qualifie, Lesson* cour, People* people);
    Prof* getAvailableProf(QVector<Prof*> const& qualifie, QDateTime debut, QDateTime fin);

protected:
    virtual void Analyser() =0;
    virtual void Appliquer() =0;
    QDateTime checkDateTime(QDateTime current);

};

class Standard: public Strategie
{
    void Analyser() {;}
    void Appliquer() {;}
public:
    Standard(QVector<Prof*> const& profs, QVector<Room*> const& rooms,
             QMap<QString, Syllabus*> const &matiere, QList<TimeSlot*> & list, QList<QDate> const& ferie);
    QDateTime checkDateTime(QDateTime & current);

};

class Defensive: public Strategie
{
    void Analyser() {;}
    void Appliquer() {;}
    QDateTime checkDateTime(QDateTime & current);
};

#endif // STOWE_H

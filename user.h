#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <QVector>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <ostream>
#include <QDateTime>
#include <QDebug>


class TimeUnavailable
{
    QDateTime _debut;
    QDateTime _fin;
public:
    TimeUnavailable(QDateTime debut, QDateTime fin);
    QDateTime getDebut() const {return _debut;}
    QDateTime getFin() const {return _fin;}
};

class User
{
    static int _count;
    int _id;
    QString _name;
public:
    User(QString name ="");
    virtual QString dump() const;
    friend QDebug operator<<(QDebug os, const User &u);
    QString getName() const {return _name;}
};

class Prof : public User
{
    QStringList _matiere;
    QList<TimeUnavailable*> _indisponible;
public:
    Prof(QString, QStringList);
    QString dump() const;
    QStringList getMatiere() const {return _matiere;}
    void addIndispo(QDateTime debut, QDateTime fin){_indisponible.push_back(new TimeUnavailable(debut,fin));}
    bool isDispo(QDateTime debut, QDateTime fin);
};

class Etudiant : public User
{
public:
    Etudiant(QString);
};

class Group;
class People
{
    public:
    virtual QVector<Group*> get() =0;
    virtual QString getName()const =0;

    friend QDebug operator<<(QDebug os, const People &p){
        return os << p.getName();
    }
};

class Group : public People
{
   static int _count;
   int _id;
   QString _name;// A, B, IL...
   QVector<Etudiant*> _etudiants;


public:
   Group(QString name);
   friend QDebug operator<<(QDebug os, const Group &g);
   QString getName() const{return _name;}
   virtual QVector<Group*> get() {
       QVector<Group*> a;
       a.push_back(this);
       return a;
   }
};

class Promo : public People
{
    QString _name;//l1, l2...
    QVector<Group*> _groups;

public:
    Promo(QString name, QStringList groupes);
    friend QDebug operator<<(QDebug os, const Promo &p);
    virtual QVector<Group*> get() {return _groups;}
    QString getName()const {return _name;}

};


#endif // USERS_H

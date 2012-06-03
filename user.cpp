#include "user.h"

int User::_count = 0;
int Group::_count = 0;

User::User(QString name)
    :_name(name),_id(_count)
{
    _count++;
}
QDebug operator<<(QDebug os, const User &u) {
    os.nospace() << u.dump();
    return os.maybeSpace();
}

QString User::dump() const {
    return QString::number(_id) + ':' +_name;
}
QString Prof::dump() const {
    return User::dump() + ":" + _matiere.join(",");
}

Prof::Prof(QString name, QStringList cours)
    : User(name), _matiere(cours)
{}
bool Prof::isDispo(QDateTime current, QDateTime fin){
    for(int i =0; i < _indisponible.size(); i++){
        if(
            (_indisponible.at(i)->getDebut().toTime_t() <= current.toTime_t() && _indisponible.at(i)->getFin().toTime_t() >= current.toTime_t()) ||
            (_indisponible.at(i)->getDebut().toTime_t() <= fin.toTime_t() && _indisponible.at(i)->getFin().toTime_t() >= fin.toTime_t())
        )return false;
    }
    return true;
}

Etudiant::Etudiant(QString name)
    : User(name)
{}

Group::Group(QString name)
    :_name(name),_id(_count)
{
    for(int i =0; i <30; i++)
        _etudiants.push_back(new Etudiant("bidule"));

}

Promo::Promo(QString name, QStringList groupes)
    :_name(name)
{
    for (int i = 0; i < groupes.size(); ++i)
    {
        _groups.push_back(new Group(_name + groupes.at(i)));
    }

}
QDebug operator<<(QDebug os, const Promo &p){
    os << p._name << ":";
    for(int i=0; i < p._groups.size(); i++){
        os << *p._groups.at(i) << " ";
    }
    return os;
}
QDebug operator<<(QDebug os, const Group &g){
    return (os << g._name);
}

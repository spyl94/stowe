#include "stowe.h"
#include <QDebug>
#include <QtSql>

using namespace std;

Stowe::Stowe()
{
    loadData();
    _strategie = new Standard(_profs,_rooms,_matieres,_list,_ferie);
}

void Stowe::loadData()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("stowe.db");
    db.setUserName("root");
    db.setPassword("");
    if(!db.open()) qDebug() << "La connexion a échouée " << db.lastError().text();
    else qDebug() << "Vous êtes maintenant connecté à " << db.databaseName();

    QSqlQuery query;
    try{
        if(query.exec("SELECT * FROM profs"))
        {
            int fieldName = query.record().indexOf("name");
            int fieldMatieres = query.record().indexOf("matieres");
            while (query.next()) {
                 _profs.push_back(new Prof(query.value(fieldName).toString(),
                                           query.value(fieldMatieres).toString().split(",")));
            }
        } else throw "BDD vide";
    } catch (const char*) {return;}

    if(query.exec("SELECT * FROM rooms"))
    {
        int fieldName = query.record().indexOf("name");
        int fieldType = query.record().indexOf("type");
        int fieldCapacity = query.record().indexOf("capacity");
        while (query.next()) {
            if(query.value(fieldType).toString() == "AMPHI")
                 _rooms.push_back(new Amphi(query.value(fieldName).toString(), query.value(fieldCapacity).toInt()));
            else if(query.value(fieldType).toString() == "TD")
                 _rooms.push_back(new Td(query.value(fieldName).toString(), query.value(fieldCapacity).toInt()));
            else if(query.value(fieldType).toString() == "TP")
                 _rooms.push_back(new Tp(query.value(fieldName).toString(), query.value(fieldCapacity).toInt()));
        }
    }
    if(query.exec("SELECT * FROM promos"))
    {
        int fieldName = query.record().indexOf("name");
        int fieldGroups = query.record().indexOf("groups");
        while (query.next()) {
             _promos.push_back(new Promo(query.value(fieldName).toString(),
                                         query.value(fieldGroups).toString().split(",")));
        }
    }
    if(query.exec("SELECT * FROM programme"))
    {
        int fieldPromo = query.record().indexOf("promo");
        int fieldMatieres = query.record().indexOf("matieres");
        while (query.next()) {
            _programme.insert(query.value(fieldPromo).toString(),
                                         query.value(fieldMatieres).toString().split(","));
        }
    }
    if(query.exec("SELECT * FROM matieres"))
    {
        int fieldName = query.record().indexOf("name");
        int fieldCM = query.record().indexOf("CM");
        int fieldTD = query.record().indexOf("TP");
        int fieldTP = query.record().indexOf("TP");
        while (query.next()) {
            _matieres.insert(query.value(fieldName).toString(),new Syllabus(query.value(fieldName).toString()));
            for(int i =0; i < query.value(fieldCM).toInt(); i++) _matieres[query.value(fieldName).toString()]->addLesson(new Lesson(i,AMPHI,90,
                                            query.value(fieldName).toString() + QLatin1String("cours n°") + QString::number(i)));
            for(int i =0; i < query.value(fieldTD).toInt(); i++) _matieres[query.value(fieldName).toString()]->addLesson(new Lesson(i,TD,90,
                                            query.value(fieldName).toString() + QLatin1String("cours n°") + QString::number(i)));
            for(int i =0; i < query.value(fieldTP).toInt(); i++) _matieres[query.value(fieldName).toString()]->addLesson(new Lesson(i,TP,120,
                                            query.value(fieldName).toString() + QLatin1String("cours n°") + QString::number(i) ));
        }
    }
    //_profs.push_back(new Prof("Pepper",(QStringList()<< "SDD" << "C++" << "C")));
    //_rooms.push_back(new Amphi("Amphi Bleu", 100));
    //_promos.push_back(new Promo("L1",(QStringList()<< "A" << "B" << "C" << "D")));
    //_programme.insert("L2",(QStringList()<< "C++" << "MPI" << "PROBA"));

    for(int i =0; i < _profs.size() ; i++) {
        QStringList mat = _profs.at(i)->getMatiere();
        for (int j = 0; j < mat.size(); ++j)
            if(_matieres.contains(mat.at(j))) _matieres[mat.at(j)]->addProf(_profs.at(i));
    }

    //_profs[0]->addIndispo(QDateTime::currentDateTime(), QDateTime::currentDateTime().addDays(1));
    //_ferie.push_back(QDate::currentDate());
}

void Stowe::addProf(QString name, QStringList mat){
    _profs.push_back(new Prof(name,mat));
    for (int j = 0; j < mat.size(); ++j)
        if(_matieres.contains(mat.at(j))) _matieres[mat.at(j)]->addProf(_profs.last());
}
void Stowe::addRoom(QString name, RoomType type, int capacity){
    switch(type){
        case AMPHI: _rooms.push_back(new Amphi(name, capacity)); break;
        case TP: _rooms.push_back(new Tp(name, capacity)); break;
        case TD: _rooms.push_back(new Td(name, capacity)); break;
    }
}
void Stowe::addFerie(QDate date){
    _ferie.push_back(date);
}

void Stowe::delProf(int i){
    _profs.remove(i);
}
void Stowe::delProf(QString name){
    _profs.remove(name.split(":").first().toInt());
}
void Stowe::delRoom(int i){
    _profs.remove(i);
}
void Stowe::delSyllabus(QString name){
    _matieres.remove(name);
}

void Stowe::addIndispo(QString name,QDateTime debut,QDateTime fin){
    _profs[name.split(":").first().toInt()]->addIndispo(debut, fin);
}
void Stowe::addSyllabus(QString name, int cm, int tp, int td){
    _matieres.insert(name,new Syllabus(name));
    for(int i =0; i < cm; i++) _matieres[name]->addLesson(new Lesson(i,AMPHI,90,
                                    name + QLatin1String("cours n°") + QString::number(i)));
    for(int i =0; i < td; i++) _matieres[name]->addLesson(new Lesson(i,TD,90,
                                    name + QLatin1String("cours n°") + QString::number(i)));
    for(int i =0; i < tp; i++) _matieres[name]->addLesson(new Lesson(i,TP,120,
                                    name + QLatin1String("cours n°") + QString::number(i)));
}

void Stowe::dump(){
    qDebug() << "DUMP Profs:";
    for (int i = 0; i < _profs.size(); ++i)
        qDebug() << *_profs.at(i);
    qDebug() << "DUMP Rooms:";
    for (int i = 0; i < _rooms.size(); ++i)
        qDebug() << *_rooms.at(i);
    qDebug() << "DUMP Promos:";
    for (int i = 0; i < _promos.size(); ++i)
        qDebug() << *_promos.at(i);
     qDebug() << "DUMP Matieres:";
     QMapIterator<QString, Syllabus*> i(_matieres);
     while (i.hasNext()){
         i.next();
         qDebug() << *i.value();
     }
}

void Stowe::generate()
{
    QMap<QString, Syllabus*>::iterator i;
    for (i = _matieres.begin(); i != _matieres.end(); ++i) //pour chaque matière
    {
        for (int j =0; j < _promos.size(); j++) { //pour chaqunes des promo
            if(_programme[_promos.at(j)->getName()].contains(i.value()->getName())){  //si la matière est au programme
                for (int k = 0; k < i.value()->getLessonsSize(); ++k){ // pour chaquns des cours de la matière
                     if (AMPHI == i.value()->getLessonsAt(k)->getType()){
                         _strategie->addTimeSlot(i.value()->getProfs(),i.value()->getLessonsAt(k),_promos.at(j));
                     }
                     else { //TD / TP
                         for (int m =0 ; m < _promos.at(j)->get().size(); m++){
                             _strategie->addTimeSlot(i.value()->getProfs(),i.value()->getLessonsAt(k),_promos.at(j)->get().at(m));
                         }
                     }
                }
            }
           qDebug() << "    promo suivante";
        }
        qDebug() << "matière suivante";
        QCoreApplication::processEvents();
    }
}


void Stowe::setStrategie(Strategie* strategie)
{
    if(strategie != 0)
    {
        delete _strategie;
        _strategie= strategie;
    }
}

Standard::Standard(QVector<Prof*> const& profs, QVector<Room*> const& rooms,
         const QMap<QString, Syllabus *> &matiere, QList<TimeSlot*> & list, const QList<QDate> &ferie)
    : Strategie(profs,rooms,matiere,list,ferie)
{}

Strategie::Strategie(QVector<Prof*> const& profs, QVector<Room*> const& rooms,
                     const QMap<QString, Syllabus *> &matiere, QList<TimeSlot*> & list, QList<QDate> const& ferie)
{
    _profs = &profs;
    _rooms = &rooms;
    _matieres = &matiere;
    _list = &list;
    _ferie= &ferie;
}

bool Strategie::addTimeSlot(QVector<Prof*> const& qualifie, Lesson* cour, People* people)
{

    //qDebug() << "J'ajoute un cours de" << cour->getName() << "pour" << people->getName();
    //on cherche la première disponibilité
    QDateTime debut= getFirstDisponibility(people,cour->getTime());
    QDateTime fin = debut.addSecs(cour->getTime()*60);

    Prof* prof = NULL;
    QVector<Room*> rooms;
    Room* room = NULL;
    try {
        if(qualifie.size()==0) throw "Pas de profs compétents";
        int tryCount = 0;
        prof = getAvailableProf(qualifie,debut,fin);
        rooms = getRoomsFree(cour->getType(),debut,fin);
        if(rooms.size() != 0) room = rooms[0];
        while (!prof  || !room ) {
            debut = getNextDisponibility(people,debut,cour->getTime());
            fin = debut.addSecs(cour->getTime()*60);
            prof = getAvailableProf(qualifie,debut,fin);
            rooms = getRoomsFree(cour->getType(),debut,fin);
            if(rooms.size() != 0) room = rooms[0];
            tryCount++;
            if(tryCount > 100) throw "Tentatives trop nombreuses";
        }
    }
    catch (const char*){
        return false;
    }
    _list->push_back(new TimeSlot(cour,prof,room,people,debut,fin));
    return true;
}


QDateTime Strategie::getFirstDisponibility(People *people, int duree){
    return (_list->size() == 0) ? checkDateTime(QDateTime::currentDateTime()) : getNextDisponibility(people,QDateTime::currentDateTime(),duree);
}
QDateTime Strategie::checkDateTime(QDateTime current){
    if(_ferie->contains(current.date())) return checkDateTime(current.addDays(1));



    if(current.time().hour() >= 18){
        current.setTime(QTime(8, 15, 0));
        current = current.addDays(1);
    }
    if(current.time().hour() <= 7) current.setTime(QTime(8, 15, 0));
    if(current.date().dayOfWeek() == 6){
        current = current.addDays(2);
        current.setTime(QTime(8, 15, 0));
    }
    if(current.date().dayOfWeek() == 7) {
        current = current.addDays(1);
        current.setTime(QTime(8, 15, 0));
    }
    return current;
}

QDateTime Strategie::getNextDisponibility(People *people, QDateTime current, int duree){
    current = checkDateTime(current);
    QDateTime fin = current.addSecs(duree*60);
    for (int i = 0; i < _list->size(); ++i) {
        //si contient la population et que le cours est compris entre le début et la fin
        if (containPeopleAt(i,people)) {
           if (_list->at(i)->getDebut().toTime_t() <= current.toTime_t() && _list->at(i)->getFin().toTime_t() >= current.toTime_t())
                return getNextDisponibility(people,_list->at(i)->getFin().addSecs(15*60),duree);
           if(_list->at(i)->getDebut().toTime_t() <= fin.toTime_t() && _list->at(i)->getFin().toTime_t() >= fin.toTime_t())
                return getNextDisponibility(people,_list->at(i)->getFin().addSecs(15*60),duree);
        }
    }
    //qDebug() << "J'ai choisit:" << current;
    return current;
}

Prof* Strategie::getAvailableProf(QVector<Prof*> const& qualifie, QDateTime current, QDateTime fin){
   QVector<Prof*> available;
    for (int i = 0; i < qualifie.size(); i++) {
        if(qualifie.at(i)->isDispo(current,fin)){
            bool find = false;
            QTime time(0,0,0);
            for(int j = 0; j < _list->size(); ++j){
                if(qualifie.at(i)==_list->at(j)->getProf()){
                    if(( //occupé
                        (_list->at(j)->getDebut().toTime_t() <= current.toTime_t() && _list->at(j)->getFin().toTime_t() >= current.toTime_t()) ||
                        (_list->at(j)->getDebut().toTime_t() <= fin.toTime_t() && _list->at(j)->getFin().toTime_t() >= fin.toTime_t())
                        )){find = true;}
                   /* if(_list->at(j)->getDebut().date()==current.date())
                    {
                        int minutes = _list->at(j)->getDebut().time().minute() - _list->at(j)->getFin().time().minute();
                        int heures = _list->at(j)->getDebut().time().hour() - _list->at(j)->getFin().time().hour();
                        time = time.addSecs(heures*60*60 + minutes*60);
                    }*/
                }
            }
            //sinon il n'a pas de cours
            if(!find /*&& time.hour() <= 6*/) available.push_back(qualifie.at(i));
        }
    }
    if(available.size() != 0) return available[0]; return NULL;
}

QVector<Room*> Strategie::getRoomsFree(RoomType type, QDateTime current, QDateTime fin){
    QVector<Room*> available;
    for(int i = 0; i <_rooms->size(); i++){
        if(_rooms->at(i)->getType()==type){ //si bon type
            //on regarde si dans la liste
            bool find = false;
            for(int j = 0; j < _list->size(); ++j){
                if(_rooms->at(i)==_list->at(j)->getRoom()){
                    if(( //occupé
                        (_list->at(j)->getDebut().toTime_t() <= current.toTime_t() && _list->at(j)->getFin().toTime_t() >= current.toTime_t()) ||
                        (_list->at(j)->getDebut().toTime_t() <= fin.toTime_t() && _list->at(j)->getFin().toTime_t() >= fin.toTime_t())
                        )){find = true;}
                }
            }
            //sinon
            if(!find) available.push_back(_rooms->at(i));
        }
    }
    return available;
}

bool Strategie::containPeopleAt(int i, People* people){
    //qDebug() << "recherche" << people->getName() << _list->at(i)->getPeople()->getName();
    if(_list->at(i)->getPeople()->getName() == people->getName()) return true; //si même groupe ou mm promo
    if(people->getName().contains(_list->at(i)->getPeople()->getName())) return true;
    //si promo alors qu'on envoit un groupe return true;
    return false;
}
void Stowe::dumpTimeList(){
    qDebug() << "DUMP TimeList:";
    for(int i = 0; i < _list.size(); i++) qDebug() << *_list.at(i);
}

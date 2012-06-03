#include "time.h"

TimeSlot::TimeSlot(Lesson* cour,Prof* prof,Room* room,People* people,QDateTime debut, QDateTime fin)
    :_cour(cour),_prof(prof),_room(room),_people(people),_debut(debut),_fin(fin)
{}
TimeUnavailable::TimeUnavailable(QDateTime debut, QDateTime fin)
    :_debut(debut),_fin(fin)
{}

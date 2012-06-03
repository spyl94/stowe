#include "syllabus.h"

Syllabus::Syllabus(QString name)
    : _name(name)
{}

void  Syllabus::addLesson(Lesson* const& cour)
{
   _lessons.push_back(cour);
}
void  Syllabus::addProf(Prof* const& prof)
{
   _profs.push_back(prof);
}

Lesson::Lesson(int id, RoomType type, int time, QString name)
    :_id(id),_type(type),_time(time),_name(name)
{

}

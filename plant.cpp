/*
James Hanenburg   Dec2019
PLant Class for plant schedule

stores a plants name and days between each required water
and can have a list of date set up for 12 weeks
*/

#include "plant.h"

#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QDate>
using namespace std;

plant::plant()                  //Constructors
{
    this->pname = "plant";
    this->days = 2;
}
plant::plant(QString n, int d):pname(n),days(d)
{
}


QString plant::getName()        //Get-set functions
{
    return pname;
}
QDate plant::getDate(int i){
    QDate q1;
    q1=date.value(i);
    return q1;
}
int plant::getDays(){
    return days;
}
void plant::setName(QString newName)
{
    this->pname = newName;
}
void plant::setDays(int length)
{
    this->days = length;
}

void plant::dates(){            //this creates the list of dates that the plant requires watering
QDate now(2019,12,15);          //requires updating to current date(YYYY,MM,DD)
int dayW;

//determines the start date

dayW=now.dayOfWeek();
if(dayW==1){now=now.addDays(7);}else if(dayW==2){now=now.addDays(6);} else if(dayW==3){now=now.addDays(5);}else
if(dayW==4){now=now.addDays(4);}else if(dayW==5){now=now.addDays(3);} else if(dayW==6){now=now.addDays(2);}
 else if(dayW==7){now=now.addDays(1);}

//fills an array the days for 12 weeks that plants need to be planted
date.clear();
date.append(now);
QDate day;
for(int i=days;i<84;i=i+days){
    day = now.addDays(i);
if(day.dayOfWeek()==7){
    day=day.addDays(1);
    i=i+1;
    }
    date.append(day);
}

}


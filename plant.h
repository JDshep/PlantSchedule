/*
James Hanenburg   Dec2019
PLant Class initilization for plant schedule
  */

#ifndef PLANT_H
#define PLANT_H


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

class plant{

    public:
    plant();
    plant(QString n, int d);
    QString getName();
    void setName(QString newname);
    void setDays(int length);
    void dates();
    QDate getDate(int i);
    QList<QDate> date;
    int getDays();



   private:
       QString pname;
       int days;

   };

#endif // PLANT_H

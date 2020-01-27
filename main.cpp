/*
James Hanenburg   Dec2019
Main Program

Runs the logic to create and Display a List of Dates and which plant to be watered that day
list covers the next 12 weeks starting on the soonest monday
*/

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
#include <plant.h>
using namespace std;


int main(int argc, char *argv[])
{
    QList<QString> fromFile;

//reading from json file and filling a list with the contents
    QFile file("D:/QT/PlantSchedule/Apprentice_WeGrowInTandem_Data.json");                      //requires exact File save location
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            qWarning() << "Could not open file!";
        }
        const auto& data = QString(file.readAll());
        file.close();

        QRegularExpression regex("\\[|\\]");
        const auto& jsons = data.split(regex);

        for(const auto& json : jsons)
            if(!json.trimmed().isEmpty()){
                const auto& formattedJson = QString("[%1]").arg(json);
                const auto& doc = QJsonDocument::fromJson(formattedJson.toUtf8());

                if(doc.isArray())
                    for(const auto& item : doc.array()){
                        const auto& obj = item.toObject();
                        const auto& keys = obj.keys();

                        for(const auto& key : keys){
                               //qDebug() << key << obj[key].toString()<<endl;
                                fromFile.append(obj[key].toString());               //fill array with content of file

                        }
                    }
            }

    //start seperateing names and number into seperate arrays
        QString name;
        QString days;
        int number;
        QList<QString> names;
        QList<int> days1;
   for(int i =0;i<(11);i++){
        name=fromFile.takeFirst();
        //qDebug() << name;             testing if names were corrct
        days=fromFile.takeFirst();
        days= days.split(" ")[0];
        number=days.toInt();
        //qDebug() <<number;            testing if numbers were correct
        names.append(name);
       days1.append(number);

    }


//creates list of plants
   QList<plant> plants;
   plant p1;
   for(int i =0; i<11;i++){
        //qDebug()<< days1.value(0);         commented parts were made to test accuary
        p1.setDays(days1.takeFirst());
        //qDebug()<<names.value(0);
       p1.setName(names.takeFirst());
       p1.dates();
       plants.append(p1);
   }

            //determine start date
   QList<QString> plantList;
   QDate now(2019,12,15);               //Requires an update to the current date
   int dayW;
   dayW=now.dayOfWeek();
   if(dayW==1){now=now.addDays(7);}else if(dayW==2){now=now.addDays(6);} else if(dayW==3){now=now.addDays(5);}else
   if(dayW==4){now=now.addDays(4);}else if(dayW==5){now=now.addDays(3);} else if(dayW==6){now=now.addDays(2);}
    else if(dayW==7){now=now.addDays(1);}



   /*qDebug()<<plants.size();              this commented section was to ensure the plant class was assigning proper dates

    for(int j=0; j< plants.size();j++){
        qDebug()<<plants.value(j).getName()<<" "<<plants.value(j).getDays();
    }
    int k=1;
    for(int i=0; i<16;i++){
        qDebug()<<plants.value(k).getDate(i).day();

    now = now.addDays(i);
    }*/



   QString dname;                   //display dates by comparing current day with each plants date list
for(int i=0; i< 7*12;i++){

       for(int j=0; j< plants.size();j++){
            for(int k=0;k<plants.value(j).date.size();k++){
                if(now.year()==plants.value(j).date.value(k).year()&&now.month()==plants.value(j).date.value(k).month()&&now.day()==plants.value(j).date.value(k).day()){
                    plantList.append(plants.value(j).getName());
                    //qDebug() <<k<<j<< plants.value(j).getName();
                    break;
                }
            }}
       if(now.dayOfWeek()==1){dname="Monday";}else if(now.dayOfWeek()==2){dname="Tuesday";} else if(now.dayOfWeek()==3){dname="Wednesday";}else
       if(now.dayOfWeek()==4){dname="Thursday";}else if(now.dayOfWeek()==5){dname="Friday";} else if(now.dayOfWeek()==6){dname="Saturday";}
        else if(now.dayOfWeek()==7){dname="Sunday";}
       if(plantList.empty()){
           qDebug() <<" no watering required:"<<dname<<","<<now.year()<<"/"<<now.month()<<"/"<<now.day()<<endl;
       }else{
       qDebug() <<"plants to be watered on"<<dname<<","<<now.year()<<"/"<<now.month()<<"/"<<now.day()<<endl;
       }
       while(!(plantList.empty())){
        qDebug() <<plantList.takeFirst()<<endl;
       }
        plantList.clear();
        now = now.addDays(1);
    }
    QCoreApplication a(argc, argv);

    return a.exec();
}

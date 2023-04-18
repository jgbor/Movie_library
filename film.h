//
// Created by Gabo on 2021.04.16..
//

#ifndef HAZIFELADAT_FILM_H
#define HAZIFELADAT_FILM_H

#include "memtrace.h"
#include "string5.h"
#include <iostream>

///Film õsosztály
class Film{
    String cim,rendezo,kategoria;
    int hossz,ev;
public:
    //konstruktor
    Film(const String& cim,const String& rend,const String& kat,int hossz,int ev): cim(cim),rendezo(rend),kategoria(kat),hossz(hossz),ev(ev){}

    //adattagok elérésére szolgaló függvények
    String getCim() const;
    String getRendezo() const;
    String getKategoria() const;
    int getHossz() const;
    int getEv() const;
    //A Dokumentum getLeiras eléréséhez, ha egy Film pointer változónk van a listában
    virtual String getLeiras() const{ return "";}
    //Az Akcio és a Csaladi getKor eléréséhez, ha egy Film pointer változónk van a listában
    virtual int getKorhatar() const{ return 0;}

    //a film adatainak kiírása a képernyõre
    virtual void kiir() const=0;

    //a film adatainak kiírása egy fájlba
    virtual void fajlba(std::ofstream& out) const =0;

    //clone fgv
    virtual Film* clone() const=0;

    //== oprátor
    bool operator==(const Film& f) const;

    //destruktor
    virtual ~Film() {}
};



#endif //HAZIFELADAT_FILM_H

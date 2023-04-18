//
// Created by Gabo on 2021.04.16..
//

#ifndef HAZIFELADAT_FILM_H
#define HAZIFELADAT_FILM_H

#include "memtrace.h"
#include "string5.h"
#include <iostream>

///Film �soszt�ly
class Film{
    String cim,rendezo,kategoria;
    int hossz,ev;
public:
    //konstruktor
    Film(const String& cim,const String& rend,const String& kat,int hossz,int ev): cim(cim),rendezo(rend),kategoria(kat),hossz(hossz),ev(ev){}

    //adattagok el�r�s�re szolgal� f�ggv�nyek
    String getCim() const;
    String getRendezo() const;
    String getKategoria() const;
    int getHossz() const;
    int getEv() const;
    //A Dokumentum getLeiras el�r�s�hez, ha egy Film pointer v�ltoz�nk van a list�ban
    virtual String getLeiras() const{ return "";}
    //Az Akcio �s a Csaladi getKor el�r�s�hez, ha egy Film pointer v�ltoz�nk van a list�ban
    virtual int getKorhatar() const{ return 0;}

    //a film adatainak ki�r�sa a k�perny�re
    virtual void kiir() const=0;

    //a film adatainak ki�r�sa egy f�jlba
    virtual void fajlba(std::ofstream& out) const =0;

    //clone fgv
    virtual Film* clone() const=0;

    //== opr�tor
    bool operator==(const Film& f) const;

    //destruktor
    virtual ~Film() {}
};



#endif //HAZIFELADAT_FILM_H

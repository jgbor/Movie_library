//
// Created by Gabo on 2021.04.19..
//

#ifndef LISTA_H_DOKUMENTUM_H
#define LISTA_H_DOKUMENTUM_H

#include "film.h"
#include "string5.h"

//Dokumentum
class Dokumentum:public Film{
    String leiras;
public:
    //konstruktor
    Dokumentum(const String& cim,const String& rend,int hossz,int ev,const String& li): Film(cim,rend,"Dokumentum",hossz,ev),leiras(li){}

    //korhatar elérésére függvény
    String getLeiras() const;

    //adatokat kiíró függvény
    void kiir() const;

    //a film adatainak kiírása egy fájlba
    void fajlba(std::ofstream &out) const;

    //clone fgv
    Dokumentum* clone() const{
        return new Dokumentum(*this);
    }

    //destruktor
    ~Dokumentum();
};

#endif //LISTA_H_DOKUMENTUM_H

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

    //korhatar el�r�s�re f�ggv�ny
    String getLeiras() const;

    //adatokat ki�r� f�ggv�ny
    void kiir() const;

    //a film adatainak ki�r�sa egy f�jlba
    void fajlba(std::ofstream &out) const;

    //clone fgv
    Dokumentum* clone() const{
        return new Dokumentum(*this);
    }

    //destruktor
    ~Dokumentum();
};

#endif //LISTA_H_DOKUMENTUM_H

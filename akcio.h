//
// Created by Gabo on 2021.04.19..
//

#ifndef LISTA_H_AKCIO_H
#define LISTA_H_AKCIO_H

#include "film.h"
#include "string5.h"

//Akciófilm
class Akcio:public Film{
    int korhatar;
public:
    //konstruktor
    Akcio(const String& cim,const String& rend,int hossz,int ev,int kh): Film(cim,rend,"Akcio",hossz,ev),korhatar(kh){}

    //korhatar elérésére függvény
    int getKorhatar() const;

    //adatokat kiíró függvény
    void kiir() const;

    //a film adatainak kiírása egy fájlba
    void fajlba(std::ofstream &out) const;

    //clone fgv
    Akcio* clone() const{
        return new Akcio(*this);
    }

    //destruktor
    ~Akcio();

};

#endif //LISTA_H_AKCIO_H

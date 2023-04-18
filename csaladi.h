//
// Created by Gabo on 2021.04.19..
//

#ifndef LISTA_H_CSALADI_H
#define LISTA_H_CSALADI_H

#include "film.h"
#include "string5.h"

//Csal�di film
class Csaladi:public Film{
    int korhatar;
public:
    //konstruktor
    Csaladi(const String& cim, const String& rend, int hossz, int ev, int kh): Film(cim, rend,"Csaladi", hossz, ev), korhatar(kh){}

    //korhatar el�r�s�re f�ggv�ny
    int getKorhatar() const;

    //adatokat ki�r� f�ggv�ny
    void kiir() const;

    //a film adatainak ki�r�sa egy f�jlba
    void fajlba(std::ofstream &out) const;

    //clone fgv
    Csaladi* clone() const{
        return new Csaladi(*this);
    }

    //destruktor
    ~Csaladi();
};

#endif //LISTA_H_CSALADI_H

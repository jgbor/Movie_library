//
// Created by Gabo on 2021.04.16..
//

#include "film.h"
#include "memtrace.h"

///Film oszt�ly
//adattagok el�r�s�re szolgal� f�ggv�nyek
String Film::getCim() const{
    return cim;
}

String Film::getRendezo() const{
    return rendezo;
}

String Film::getKategoria() const{
    return kategoria;
}

int Film::getHossz() const{
    return hossz;
}

int Film::getEv() const{
    return ev;
}

/*== opr�tor, mivel egy filmnek lehet egyforma c�me, rendez�je, t�bb v�ltozat eset�n a hossz �s az �v v�ltozhat,
 * �gy akkor lesz egyenl� k�t film, ha ezek az adataik mind megegyeznek*/
bool Film::operator==(const Film& f) const{
    return cim==f.getCim() && ev==f.getEv() && rendezo==f.getRendezo() && hossz==f.getHossz() && kategoria==f.getKategoria();
}
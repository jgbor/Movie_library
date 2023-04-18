//
// Created by Gabo on 2021.04.16..
//

#include "film.h"
#include "memtrace.h"

///Film osztály
//adattagok elérésére szolgaló függvények
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

/*== oprátor, mivel egy filmnek lehet egyforma címe, rendezõje, több változat esetén a hossz és az év változhat,
 * így akkor lesz egyenlõ két film, ha ezek az adataik mind megegyeznek*/
bool Film::operator==(const Film& f) const{
    return cim==f.getCim() && ev==f.getEv() && rendezo==f.getRendezo() && hossz==f.getHossz() && kategoria==f.getKategoria();
}
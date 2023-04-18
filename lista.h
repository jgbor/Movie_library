//
// Created by Gabo on 2021.04.16..
//

#ifndef HAZIFELADAT_LISTA_H
#define HAZIFELADAT_LISTA_H

#include "memtrace.h"
#include "film.h"
#include "csaladi.h"
#include "akcio.h"
#include "dokumentum.h"
#include "string5.h"

struct Listaelem{
    Film* adat;
    Listaelem* kov;
};

class Lista {
    Listaelem* elso;
    static int fajtadb;
    String fajtak[3]={"Csaladi","Akcio","Dokumentum"};


    //megmondja, hogy egy konkr�t film benne van-e a list�ban
    bool bennevan(Film* f) const;

    //megmondja egy filmr�l h�nyas kateg�ri�ba tartozik
    int milyenfajta(String& kat) const;

    //bek�ri egy film adatait
    Film* filmbeker() const;

    //egy filmet a list�ba helyez
    void belerak(Film*& f);

public:
    //konstruktor
    Lista():elso(nullptr){}

    //f�jlb�l megalkotja a a list�t
    void fajlbeolvas();

    //a list�t f�jlba ki�r� f�ggv�ny
    void fajlkiir();

    //teljes list�t k�perny�re ki�r� f�ggv�ny
    void kiir() const;

    //els� elemre mutat� pointert visszaad� f�ggv�ny
    Listaelem* getElso() const;

    //a felhaszn�l� �j elemet adhat a list�hoz
    void hozzaad();

    //a felhaszn�l� t�r�lhet elemet a list�b�l
    void torol();

    //a felhaszn�l� sz�rheti az adatb�zisban l�v� filmeket
    void szures(bool* opciok);

    //egy karaktersorozatot megadva keres a filmek String adatai k�z�tt
    void keresbarmiben();

    //destruktor
    ~Lista();
};

#endif //HAZIFELADAT_LISTA_H

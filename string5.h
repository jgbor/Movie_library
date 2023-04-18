#ifndef STRING_H
#define STRING_H
/**
 * \file string5.h
 *
 * Ez a f�jl tartalmazza a
 *   - String oszt�ly deklar�ci�j�t
 *   - az inline f�ggv�nyeket.*/

#include <iostream>

#ifndef MEMTRACE
#error "definialja projekt szinten a MEMTARCE makrot!"
#endif // MEMTRACE

/**
 * A String oszt�ly.
 * A 'pData'-ban vannak a karakterek (a lez�r� null�val egy�tt), 'len' a hossza.
 * A hosszba nem sz�m�t bele a lez�r� nulla.
 *
 * Kor�bban a len adattag unsigned int t�pus� volt. Most helyette a size_t t�pust haszn�ljuk.
 * Ezzel a t�pussal t�r vissza a sizeof operator is, k�s�bb t�bb helyen ezt haszn�ljuk
 * m�rett�pusk�nt.

 */
class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lez�r� nulla n�lk�l
public:

    /// Param�ter n�lk�li konstruktor:
    String() :pData(nullptr), len(0){}

    /// Sztring hossz�t adja vissza.
    /// @return sztring t�nyleges hossza (lez�r� nulla n�lk�l).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a t�rolt, vagy azzal azonos tartalm� null�val lez�rt sztring-re.
    ///    NULL-t t�rol, de a c_str() �res sztringet ad vissza helyette
    const char* c_str() const {
        if (len!=0) {
            return pData;
        }else{
            return "";
        }
    }

    ///konstruktor, ami karakterb�l hoz l�tre sztringet
    String(char c);

    ///konstruktor, ami C-sztringb�l (const char*) hoz l�tre sztringet.
    String(const char* s);

    ///M�sol� konstruktor
    String(const String& s);

    ///Destruktor
    ~String();

    ///�rt�kad�
    String& operator=(const String& s);

    ///�sszead�k
    String operator+(const String& s) const;
    String operator+(char c) const;

    ///[] oper�tor
    char& operator[](unsigned int i);
    const char& operator[](unsigned int i) const;

    ///== oper�tor
    bool operator==(const String& s) const;

    ///String-b�l C t�pus� sztringg� konverzi� a <ctring> f�ggv�nyeihez val� kompatibilit�s v�gett
    operator char*() const;


}; /// Itt az oszt�ly deklar�ci�j�nak v�ge

/// Ide ker�lnek a glob�lis oper�torok deklar�ci�i.

String operator+(char c, const String& s);

///>> �s << oper�tor
std::istream& operator>>(std::istream& is, String& s);
std::ostream& operator<<(std::ostream& out,const String& s);



#endif

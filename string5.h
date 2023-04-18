#ifndef STRING_H
#define STRING_H
/**
 * \file string5.h
 *
 * Ez a fájl tartalmazza a
 *   - String osztály deklarációját
 *   - az inline függvényeket.*/

#include <iostream>

#ifndef MEMTRACE
#error "definialja projekt szinten a MEMTARCE makrot!"
#endif // MEMTRACE

/**
 * A String osztály.
 * A 'pData'-ban vannak a karakterek (a lezáró nullával együtt), 'len' a hossza.
 * A hosszba nem számít bele a lezáró nulla.
 *
 * Korábban a len adattag unsigned int típusú volt. Most helyette a size_t típust használjuk.
 * Ezzel a típussal tér vissza a sizeof operator is, késõbb több helyen ezt használjuk
 * mérettípusként.

 */
class String {
    char *pData;        ///< pointer az adatra
    size_t len;         ///< hossz lezáró nulla nélkül
public:

    /// Paraméter nélküli konstruktor:
    String() :pData(nullptr), len(0){}

    /// Sztring hosszát adja vissza.
    /// @return sztring tényleges hossza (lezáró nulla nélkül).
    size_t size() const { return len; }

    /// C-sztringet ad vissza
    /// @return pointer a tárolt, vagy azzal azonos tartalmú nullával lezárt sztring-re.
    ///    NULL-t tárol, de a c_str() üres sztringet ad vissza helyette
    const char* c_str() const {
        if (len!=0) {
            return pData;
        }else{
            return "";
        }
    }

    ///konstruktor, ami karakterbõl hoz létre sztringet
    String(char c);

    ///konstruktor, ami C-sztringbõl (const char*) hoz létre sztringet.
    String(const char* s);

    ///Másoló konstruktor
    String(const String& s);

    ///Destruktor
    ~String();

    ///értékadó
    String& operator=(const String& s);

    ///összeadók
    String operator+(const String& s) const;
    String operator+(char c) const;

    ///[] operátor
    char& operator[](unsigned int i);
    const char& operator[](unsigned int i) const;

    ///== operátor
    bool operator==(const String& s) const;

    ///String-bõl C típusú sztringgé konverzió a <ctring> függvényeihez való kompatibilitás végett
    operator char*() const;


}; /// Itt az osztály deklarációjának vége

/// Ide kerülnek a globális operátorok deklarációi.

String operator+(char c, const String& s);

///>> és << operátor
std::istream& operator>>(std::istream& is, String& s);
std::ostream& operator<<(std::ostream& out,const String& s);



#endif

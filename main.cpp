#include "memtrace.h"
#include "lista.h"
#include "teszt-menu.h"

int main() {

    #ifdef CPORTA //Jport�n lefut� r�sz
        teszteles();
    #else //saj�t g�pen lefut� r�sz
        felhasznalo();
    #endif

    return 0;
}

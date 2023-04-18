#include "memtrace.h"
#include "lista.h"
#include "teszt-menu.h"

int main() {

    #ifdef CPORTA //Jportán lefutó rész
        teszteles();
    #else //saját gépen lefutó rész
        felhasznalo();
    #endif

    return 0;
}

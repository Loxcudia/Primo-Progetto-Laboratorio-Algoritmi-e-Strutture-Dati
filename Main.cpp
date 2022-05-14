#include <stdio.h>
#include "Funzioni.h"
int main()
{
    Utente* u = NULL;
    CapiDiAbbigliamento* c = NULL;
    ListaDiAttesa* l = NULL;
    Admin* a = NULL;
    a = standardizzazioneAdmin(a);
    c = standardizzazioneCapiDiAbbigliamento(c);
    //inorderVisit(c);
    u = standardizzazioneUtenti(u);
    //visualizzaUtenti(u);
    menu(u, c, l, a);
    liberaAlberoBinario(c);
    liberaAdmin(a);
    liberaUtenti(u);
    liberaListaDiAttesa(l);
    return 0;
}

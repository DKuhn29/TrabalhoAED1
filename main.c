#include <locale.h>
#include "generos.h"
#include "interface.h"
#include <windows.h>

int main(){
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "Portuguese_Brazil.UTF8");
    ListaGeneros listaG;
    inicializarLista(&listaG);
     carregarBancoDeDados(&listaG, "tex.txt");
    executarMenuPrincipal(&listaG);

    return 0;
}

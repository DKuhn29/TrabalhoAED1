#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generos.h"

int main(){






    int i = 0;
    char musica[40];
    char album[40];
    while(i != qtdmusicas){
        setbuf(stdin, NULL);
        fgets(musica, 40, stdin);
        fgets(album, 40, stdin);
        inserirMusica(novo, musica, album);
    }


    }

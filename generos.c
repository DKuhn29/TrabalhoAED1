#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generos.h"

// Cria a lista de generos
void inicializarLista(ListaGeneros *l){
    l->ini = NULL;
}

// Insere um genero novo na lista
void inserirGenero(ListaGeneros *l, char nome[]){
    Genero *novo = (Genero*) malloc(sizeof(Genero));
    if(novo == NULL){
        printf("Erro ao inserir Genero\n");
        return;
    }
    strcpy(novo->nome, nome);
    novo->listaArtistas = NULL;
    novo->prox = l->ini;
    novo->ant = NULL;
    
    if(l->ini != NULL){
        l->ini->ant = novo;
    }
    l->ini = novo;
}

Genero* buscarGenero(ListaGeneros *l, char nome[]){
    Genero *atual = l->ini;
    while(atual!= NULL){
        if(strcmp(atual->nome, nome) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


void alterarGenero(ListaGeneros *l, char nomeAntigo[], char nomeNovo[]){
    Genero *atual = buscarGenero(l, nomeAntigo);
    if(atual == NULL){
        printf("Genero nao encontrado\n");
        return;
    }
    strcpy(atual->nome, nomeNovo);
    printf("Nome alterado com sucesso\n");

}
void removerGenero(ListaGeneros *l, char nome[]){
    Genero *atual = buscarGenero(l, nome);
    if(atual == NULL){
        printf("Genero nao encontrado\n");
        return;
    }
    atual->prox->ant = atual->ant;
    atual->ant->prox = atual->prox;
    //LEMBRAR FREE


}

void listarGeneros(ListaGeneros *l){
    Genero *atual = l->ini;
    printf("Lista de generos: ");
    while(atual->prox!=NULL){
        printf("%s - ", atual->nome);
        atual = atual ->prox;
    }
    if(atual != NULL){
        printf("%s\n", atual->nome);
    }
}


int contarGeneros(ListaGeneros *l){
    int contador = 0;
    Genero *atual = l->ini;
    while(atual != NULL){
        contador++;
        atual = atual->prox;
    }
    return contador;
}

void destruirLista(ListaGeneros *l){
    if(l == NULL){
        return;
    }
    Genero *atual = l->ini;
    Genero *prox;
    while(atual != NULL){
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    l->ini = NULL;
    //DESTRUIR LISTA DE DENTRO AAAAAAA
}

//  Funcões da segunda lista
void inserirArtista(ListaGeneros *l, char nomeGenero[]){
    Genero *atual = buscaGenero(l, nomeGenero);
    
}


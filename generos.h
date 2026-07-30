#include <stdbool.h>
#ifndef _GENEROS_H
#define _GENEROS_H

// Lista de Músicas
typedef struct mus {
    int ano;
    char nome[40];
    char album[40];
    struct mus *prox;
} Musica;

// Lista de Artistas
typedef struct no1 {
    char nome[30];
    char cidadeOrigem[30];
    int anosAtuacao;
    bool aindaAtua;
    int premiacoes;
    char integrantes[200];
    Musica *listaMusicas; // Ponteiro para a lista encadeada de músicas
    struct no1 *prox;
} Artista;

// Lista Duplamente Encadeada de Gêneros 
typedef struct no {
    char nome[15];
    struct no *ant;
    struct no *prox;
    Artista *listaArtistas; // Ponteiro para a lista encadeada de artistas
} Genero;

// No Descritor Para Gêneros
typedef struct lista{
    Genero *ini;
} ListaGeneros;


// Funções Gêneros 
void inicializarLista(ListaGeneros *l);
void inserirGenero(ListaGeneros *l, char nome[]);
Genero *buscarGenero(ListaGeneros *l, char nome[]);
void alterarGenero(ListaGeneros *l, char nomeAntigo[], char nomeNovo[]);
void removerGenero(ListaGeneros *l, char nome[]);
void listarGeneros(ListaGeneros *l);
int contarGeneros(ListaGeneros *l);
void destruirLista(ListaGeneros *l);

//Funções Artistas
void inserirArtista()

#endif
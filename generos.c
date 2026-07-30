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
        destruirArtistas(atual, atual->nome);
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    l->ini = NULL;
    free(l);
    
}

//  Funcões da segunda lista
void inserirArtista(ListaGeneros *l, char nomeGenero[], Artista dados){
    Genero *atual = buscaGenero(l, nomeGenero);
    if(atual == NULL){
        printf("Esse genero não esta na lista, adicione antes de adicionar o artista");
        return;
    }
     Artista *novo = (Artista*) malloc(sizeof(Artista));
    if(novo == NULL){
        printf("Erro ao inserir artista\n");
        return;
    }
    strcpy(novo->cidadeOrigem, dados.cidadeOrigem);
    strcpy(novo->integrantes, dados.integrantes);
    strcpy(novo->nome, dados.nome);
    novo->anosAtuacao = dados.anosAtuacao;
    novo->aindaAtua = dados.aindaAtua;
    novo->premiacoes = dados.premiacoes;
    novo->listaMusicas = NULL;
    novo->prox = l->ini->listaArtistas;
    novo->ant = NULL;
    
    if(l->ini->listaArtistas != NULL){
        l->ini->listaArtistas->ant = novo;
    }
    l->ini->listaArtistas = novo;

}
 void removerArtista(ListaGeneros *l, char nomeGenero[]){
  Genero *atual = buscaGenero(l, nomeGenero);
    if(atual == NULL){
        printf("Esse genero não esta na lista, nao e possivel remover o artista dele");
        return;
    }
    Artista *novo = atual->listaArtistas;
    novo->prox->ant = novo->ant;
    novo->ant->prox = novo->prox;
    //PRECISA FAZER O FREE DA LISTA DE MUSICAS DELE
    free(atual);
 }
 Artista *buscarArtista(ListaGeneros *l, char nomeGenero[], char nomeArtista[]){
    Genero *atual = buscarGenero(l, nomeGenero);
    Artista *novo = atual->listaArtistas;
    while(novo!= NULL){
        if(strcmp(novo->nome, nomeArtista) == 0){
            return novo;
        }
        novo = novo->prox;
    }
    return NULL;
}
void alterarArtista(ListaGeneros *l, char nomeAntigo[], char nomeNovo[], char dadoAlterado[]){
    Genero *atual = buscarGenero(l, nomeAntigo);
    if(atual == NULL){
        printf("Genero nao encontrado\n");
        return;
    }
    Artista *novo = buscarArtista(l, atual->nome, nomeAntigo);
    if(novo == NULL){
        printf("Artista nao encontrado\n");
        return;
    }
    if(strcmp(dadoAlterado, "Nome do Artista\n")== 0){
        strcpy(novo->nome, nomeNovo);
        printf("Nome do artista alterado com sucesso");
        return;
    }else if(strcmp(dadoAlterado, "Cidade de origem\n")== 0){
        strcpy(novo->cidadeOrigem, nomeNovo);
        printf("Nome da cidade de origem alterado com sucesso");
        return;
    }else if(strcmp(dadoAlterado, "Integrantes\n")){
        strcpy(novo->integrantes, nomeNovo);
        printf("Nome dos integrantes alterado com sucesso");
        return;
    }
        printf("Nao foi possivel alterar o dado");
        return;
    }
    int contarArtistas(ListaGeneros *l, char nomeGenero[]){
    int contador = 0;
    Genero *atual = buscarGenero(l, nomeGenero);
    if(atual == NULL){
        printf("O genero nao esta presente na lista, adicione-o antes de contar a lista");
        return;
    }
    Artista *novo = atual->listaArtistas;
    while(novo != NULL){
        contador++;
        novo = novo->prox;
    }
    return contador;
}
void destruirArtistas(ListaGeneros *l, char nomeGenero[]){
    Genero *atual = buscarGenero(l, nomeGenero);
    if(atual == NULL){
        printf("nao e possivel destruir a lista de artistas, pois o genero nao foi encontrado");
    }
    Artista *novo = atual->listaArtistas;
    Artista *prox;
    while(novo != NULL){
        prox = novo->prox;
        free(novo);
        novo = prox;
    }
    atual->listaArtistas = NULL;
}


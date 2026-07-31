#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generos.h"

// DEFINIÇÃO DAS ESTRUTURAS
struct mus{
    char nome[40];
    char album[40];
    struct mus *prox;
};

struct no1{
    char nome[30];
    char cidadeOrigem[30];
    int anosAtuacao;
    bool aindaAtua;
    int premiacoes;
    char integrantes[200];
    Musica *listaMusicas;
    struct no1 *prox;
    struct no1 *ant;
};

struct no{
    char nome[15];
    struct no *ant;
    struct no *prox;
    Artista *listaArtistas;
};


// FUNÇÕES DE MÚSICAS (BÁSICAS)
void destruirMusicas(Musica *iniMusicas){
    Musica *atual = iniMusicas;
    Musica *prox;
    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
void inserirMusica(Artista *art, char nome[], char album[]){
    if (art == NULL){
        return;
    }
    Musica *nova = (Musica*) malloc(sizeof(Musica));
    if (nova == NULL){
        printf("Erro ao alocar memoria para a musica.\n");
        return;
    }

    strcpy(nova->nome, nome);
    strcpy(nova->album, album);
    nova->prox = art->listaMusicas;
    art->listaMusicas = nova;
}

void listarMusicasDoArtista(Artista *art){
    if (art == NULL || art->listaMusicas == NULL){
        printf("Nenhuma musica cadastrada)\n");
        return;
    }

    Musica *atual = art->listaMusicas;
    printf("      Musicas:\n");
    while (atual != NULL) {
        printf("       - Faixa: %s | Album: %s\n", atual->nome, atual->album);
        atual = atual->prox;
    }
}


//FUNÇÕES OBRIGATÓRIAS - 2ª LISTA (ARTISTAS)

//  Insere Artista
void inserirArtista(ListaGeneros *l, char nomeGenero[], char nome[], char cidadeOrigem[], int anosAtuacao, bool aindaAtua, int premiacoes, char integrantes[]){
    Genero *gen = buscarGenero(l, nomeGenero);
    if (gen == NULL) {
        printf("Genero '%s' nao encontrado\n", nomeGenero);
        return;
    }

    Artista *novo = (Artista*) malloc(sizeof(Artista));
    if (novo == NULL) {
        printf("Erro ao inserir Artista\n");
        return;
    }

    // Atribuição de Dados
    strcpy(novo->nome, nome);
    strcpy(novo->cidadeOrigem, cidadeOrigem);
    strcpy(novo->integrantes, integrantes);
    novo->anosAtuacao = anosAtuacao;
    novo->aindaAtua = aindaAtua;
    novo->premiacoes = premiacoes;
    novo->listaMusicas = NULL;

    // Ajuste de Ponteiros do Gênero
    novo->prox = gen->listaArtistas;
    novo->ant = NULL;

    if (gen->listaArtistas != NULL){
        gen->listaArtistas->ant = novo;
    }
    gen->listaArtistas = novo;
}

//Busca artista
Artista* buscarArtista(ListaGeneros *l, char nomeGenero[], char nomeArtista[]){
    Genero *gen = buscarGenero(l, nomeGenero);
    if (gen == NULL) return NULL;

    Artista *atual = gen->listaArtistas;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeArtista) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

// Altera Artista
void alterarNomeArtista(Artista *art, char novoNome[]){
    if(art != NULL){
        strcpy(art->nome, novoNome);
    } 
}
void alterarCidadeArtista(Artista *art, char novaCidade[]){
    if(art != NULL){
        strcpy(art->cidadeOrigem, novaCidade);
    }
}
void alterarAnosAtuacao(Artista *art, int novosAnos){
    if(art != NULL){
        art->anosAtuacao = novosAnos;
    }
}
void alterarStatusAtuacao(Artista *art, bool aindaAtua){
    if(art != NULL){
        art->aindaAtua = aindaAtua;
    }
}
void alterarPremiacoes(Artista *art, int novasPremiacoes){
    if(art != NULL){
        art->premiacoes = novasPremiacoes;
    }
}
void alterarIntegrantes(Artista *art, char novosIntegrantes[]){
    if(art != NULL){
        strcpy(art->integrantes, novosIntegrantes);
    }
}

//  Remove artista
void removerArtista(ListaGeneros *l, char nomeGenero[], char nomeArtista[]){
    Genero *gen = buscarGenero(l, nomeGenero);
    if (gen == NULL) return;

    Artista *art = buscarArtista(l, nomeGenero, nomeArtista);
    if (art == NULL) {
        printf("Artista '%s' nao encontrado\n", nomeArtista);
        return;
    }

    if (art->ant != NULL) {
        art->ant->prox = art->prox;
    } else {
        gen->listaArtistas = art->prox;
    }

    if (art->prox != NULL) {
        art->prox->ant = art->ant;
    }

    destruirMusicas(art->listaMusicas);
    free(art);
}

// Listar Artistas do Gênero
void listarArtistas(ListaGeneros *l, char nomeGenero[]){
    Genero *gen = buscarGenero(l, nomeGenero);
    if (gen == NULL){
        printf("Genero nao encontrado\n");
        return;
    }

    Artista *atual = gen->listaArtistas;
    if (atual == NULL) {
        printf("Nenhum artista em '%s'\n", nomeGenero);
        return;
    }

    printf("\n=== Artistas de %s ===\n", nomeGenero);
    while (atual != NULL){
        printf("\nNome: %s | Cidade: %s | Anos: %d | Premios: %d | Ativo: %s | Integrantes: %s\n",
               atual->nome, atual->cidadeOrigem, atual->anosAtuacao,
               atual->premiacoes, atual->aindaAtua ? "Sim" : "Nao",
               atual->integrantes);
        
        listarMusicasDoArtista(atual);
        
        atual = atual->prox;
    }
}

// Contar Artistas
int contarArtistas(ListaGeneros *l, char nomeGenero[]) {
    Genero *gen = buscarGenero(l, nomeGenero);
    if (gen == NULL) return 0;

    int contador = 0;
    Artista *atual = gen->listaArtistas;
    while (atual != NULL) {
        contador++;
        atual = atual->prox;
    }
    return contador;
}

void destruirArtistasDoGenero(Genero *gen){
    if(gen == NULL){
        return;
    } 

    Artista *atual = gen->listaArtistas;
    Artista *prox;
    while (atual != NULL){
        prox = atual->prox;
        destruirMusicas(atual->listaMusicas);
        free(atual);
        atual = prox;
    }
    gen->listaArtistas = NULL;
}




// FUNÇÕES OBRIGATÓRIAS - 1ª LISTA (GÊNEROS)

// Cria a lista de generos
void inicializarLista(ListaGeneros *l){
    if (l != NULL) {
        l->ini = NULL;
    }
}

// Insere um gênero novo na lista
void inserirGenero(ListaGeneros *l, char nome[]){
    if(l == NULL){
        printf("Erro ao inserir Genero - lista nula\n");
        return;
    } 

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

//Buscar em genero
Genero* buscarGenero(ListaGeneros *l, char nome[]){
    if(l == NULL){
        return NULL;
    } 
    Genero *atual = l->ini;
    while(atual!= NULL){
        if(strcmp(atual->nome, nome) == 0){
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}


// Alterar dados do genero
void alterarGenero(ListaGeneros *l, char nomeAntigo[], char nomeNovo[]){
    Genero *atual = buscarGenero(l, nomeAntigo);
    if(atual == NULL){
        printf("Genero '%s' nao encontrado.\n", nomeAntigo);
        return;
    }

    strcpy(atual->nome, nomeNovo);
    printf("Nome do genero alterado com sucesso para '%s'.\n", nomeNovo);
}

// remover genero
void removerGenero(ListaGeneros *l, char nome[]){
    if(l == NULL){
        return;
    } 

    Genero *atual = buscarGenero(l, nome);
    if(atual == NULL){
        printf("Genero '%s' nao encontrado.\n", nome);
        return;
    }

    if(atual->ant != NULL){
        atual->ant->prox = atual->prox;
    } 
    else{
        l->ini = atual->prox; // Se for o primeiro da lista
    }
    if(atual->prox != NULL){
        atual->prox->ant = atual->ant;
    }

    // Libera a lista de artistas associados antes de deletar o gênero
    destruirArtistasDoGenero(atual);
    free(atual);
}

// Listar Generos
void listarGeneros(ListaGeneros *l){
    if(l == NULL || l->ini == NULL){
        printf("Lista de generos esta vazia\n");
        return;
    }

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

// Conta elementos da lista
int contarGeneros(ListaGeneros *l){
    if(l == NULL){
        return 0;
    }
    int contador = 0;
    Genero *atual = l->ini;
    while(atual != NULL){
        contador++;
        atual = atual->prox;
    }
    return contador;
}

// libera todos os generos
void destruirListaGeneros(ListaGeneros *l){
    if (l == NULL) return;

    Genero *atual = l->ini;
    Genero *prox;
    while (atual != NULL) {
        prox = atual->prox;
        destruirArtistasDoGenero(atual);
        free(atual);
        atual = prox;
    }
    l->ini = NULL;
}




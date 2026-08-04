#ifndef GENEROS_H
#define GENEROS_H

#include <stdbool.h>


typedef struct mus Musica;
typedef struct no1 Artista;
typedef struct no Genero;


typedef struct lista {
    Genero *ini;
} ListaGeneros;


// FUNÇÕES LISTA 1 (GENERO)
void inicializarLista(ListaGeneros *l);
void inserirGenero(ListaGeneros *l, char nome[]);
Genero *buscarGenero(ListaGeneros *l, char nome[]);
void alterarGenero(ListaGeneros *l, char nomeAntigo[], char nomeNovo[]);
void removerGenero(ListaGeneros *l, char nome[]);
void listarGeneros(ListaGeneros *l);
int contarGeneros(ListaGeneros *l);
void destruirListaGeneros(ListaGeneros *l);


// FUNÇÕES LISTA 2 (ARTISTAS)
void inserirArtista(ListaGeneros *l, char nomeGenero[], char nome[], char cidadeOrigem[], int anosAtuacao, bool aindaAtua, int premiacoes, char integrantes[]);
Artista *buscarArtista(ListaGeneros *l, char nomeGenero[], char nomeArtista[]);
void removerArtista(ListaGeneros *l, char nomeGenero[], char nomeArtista[]);
void listarArtistas(ListaGeneros *l, char nomeGenero[]);
int contarArtistas(ListaGeneros *l, char nomeGenero[]);
void inserirMusica(Artista *art, char nome[], char album[]);
void listarMusicasDoArtista(Artista *art);

// FUNÇÕES ALTERAÇÕES
void alterarNomeArtista(Artista *art, char novoNome[]);
void alterarCidadeArtista(Artista *art, char novaCidade[]);
void alterarAnosAtuacao(Artista *art, int novosAnos);
void alterarStatusAtuacao(Artista *art, bool aindaAtua);
void alterarPremiacoes(Artista *art, int novasPremiacoes);
void alterarIntegrantes(Artista *art, char novosIntegrantes[]);

// FUNCOES ADICIONAIS
void contabilizarArtistasPorGenero(ListaGeneros *l);
void buscarArtistasEmMultiplosGeneros(ListaGeneros *l);
void ordenarArtistasPorNome(ListaGeneros *l, char nomeGenero[]);
void gerarRelatorioGeral(ListaGeneros *l);
void gerarTop3Generos(ListaGeneros *l);
void filtarNumeroPremios(ListaGeneros *l, char nomeGenero[], int numPremios);

void carregarBancoDeDados(ListaGeneros *l, const char *nomeArquivo);
#endif

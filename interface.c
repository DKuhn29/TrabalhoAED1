#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "interface.h"
#include "generos.h"


#ifdef _WIN32
    #include <windows.h>
    #define LIMPAR_TELA() system("cls")
#else
    #define LIMPAR_TELA() system("clear")
#endif

void pausar(){
    printf("\nPressione ENTER para continuar...");
    getchar();
}

void lerString(char *buffer, int tamanho){
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

void menuAlterarArtista(ListaGeneros *l){
    char nomeGenero[70], nomeArtista[70];

    printf("\n--- ALTERAR ARTISTA ---\n");
    printf("Nome do Genero do artista: ");
    lerString(nomeGenero, sizeof(nomeGenero));

    printf("Nome do Artista que deseja alterar: ");
    lerString(nomeArtista, sizeof(nomeArtista));

    Artista *art = buscarArtista(l, nomeGenero, nomeArtista);

    if (art == NULL){
        printf("\nArtista ou Genero nao encontrado!\n");
        return;
    }

    int opcao;
    do{
        printf("\n===================================\n");
        printf(" Editando Artista: %s\n", nomeArtista);
        printf("===================================\n");
        printf("1. Alterar Nome\n");
        printf("2. Alterar Cidade de Origem\n");
        printf("3. Alterar Anos de Atuacao\n");
        printf("4. Alterar Status de Atividade (Ativo/Inativo)\n");
        printf("5. Alterar Quantidade de Premiacoes\n");
        printf("6. Alterar Integrantes\n");
        printf("0. Concluir alteracoes deste artista\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:{
            char novoNome[30];
            printf("Novo Nome: ");
            lerString(novoNome, sizeof(novoNome));
            alterarNomeArtista(art, novoNome);
            strcpy(nomeArtista, novoNome);
            printf("-> Nome alterado com sucesso!\n");
            break;
        }
        case 2:{
            char novaCidade[30];
            printf("Nova Cidade de Origem: ");
            lerString(novaCidade, sizeof(novaCidade));
            alterarCidadeArtista(art, novaCidade);
            printf("-> Cidade alterada com sucesso!\n");
            break;
        }
        case 3:{
            int anos;
            printf("Novos Anos de Atuacao: ");
            scanf("%d", &anos);
            getchar();
            alterarAnosAtuacao(art, anos);
            printf("-> Anos de atuacao alterados com sucesso!\n");
            break;
        }
        case 4:{
            int status;
            printf("O artista ainda atua? (1 - Sim / 0 - Nao): ");
            scanf("%d", &status);
            getchar();
            alterarStatusAtuacao(art, status == 1);
            printf("-> Status de atividade alterado!\n");
            break;
        }
        case 5:{
            int premios;
            printf("Nova Quantidade de Premiacoes: ");
            scanf("%d", &premios);
            getchar();
            alterarPremiacoes(art, premios);
            printf("-> Premiacoes alteradas!\n");
            break;
        }

        case 6:{
            char novosIntegrantes[200];
            printf("Novos Integrantes (separados por virgula): ");
            lerString(novosIntegrantes, sizeof(novosIntegrantes));
            alterarIntegrantes(art, novosIntegrantes);
            printf("-> Integrantes alterados com sucesso!\n");
            break;
        }

        case 0:
            printf("Finalizando alteracoes do artista.\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void executarMenuPrincipal(ListaGeneros *l){
    int opcao;

    do{
        LIMPAR_TELA();
        printf("\n===================================\n");
        printf("       SISTEMA DE MUSICA - MENU     \n");
        printf("===================================\n");
        printf("--- GENEROS MUSICAIS ---\n");
        printf("1. Inserir Genero\n");
        printf("2. Listar Generos\n");
        printf("3. Alterar Nome do Genero\n");
        printf("4. Remover Genero (com artistas/musicas)\n");
        printf("5. Contar Generos\n");
        printf("\n--- ARTISTAS / BANDAS ---\n");
        printf("6. Inserir Artista em um Genero\n");
        printf("7. Listar Artistas de um Genero\n");
        printf("8. Alterar Dados de um Artista\n");
        printf("9. Remover Artista de um Genero\n");
        printf("10. Contar Artistas de um Genero\n");
        printf("\n--- RELATORIOS E CONSULTAS --- \n");
        printf("11. Contabilizar Artistas por Genero\n");
        printf("12. Buscar Artistas em Multiplos Generos\n");
        printf("13. Ordenar Artistas por Nome (Genero especifico)\n");
        printf("14. Gerar Relatorio Geral do Sistema\n");
        printf("15. Gerar Top 3 Generos\n");
        printf("16. Filtrar Artistas por Quantidade de Premios\n");
        printf("\n0. Sair da aplicacao\n");
        printf("===================================\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao){
        case 1:{
            char nome[70];
            printf("Nome do novo Genero: ");
            lerString(nome, sizeof(nome));
            inserirGenero(l, nome);
            break;
        }
        case 2:
            listarGeneros(l);
            break;
        case 3:{
            char antigo[70], novo[70];
            printf("Nome do Genero atual: ");
            lerString(antigo, sizeof(antigo));
            printf("Novo nome para o Genero: ");
            lerString(novo, sizeof(novo));
            alterarGenero(l, antigo, novo);
            break;
        }
        case 4:{
            char nome[70];
            printf("Nome do Genero a remover: ");
            lerString(nome, sizeof(nome));
            removerGenero(l, nome);
            break;
        }
        case 5:
            printf("\nTotal de generos cadastrados: %d\n", contarGeneros(l));
            break;
        case 6:{
            char genNome[70], nomeArt[70], cidade[70], integrantes[200];
            int anos, premios, ativoInt;

            printf("Em qual Genero deseja cadastrar? ");
            lerString(genNome, sizeof(genNome));


            if (buscarGenero(l, genNome) == NULL){
                printf("Genero '%s' nao foi encontrado!\n", genNome);
                break;
            }

            printf("Nome do Artista/Banda: ");
            lerString(nomeArt, sizeof(nomeArt));

            printf("Cidade de Origem: ");
            lerString(cidade, sizeof(cidade));

            printf("Anos de Atuacao: ");
            scanf("%d", &anos);
            getchar();

            printf("Ainda esta em atividade? (1 - Sim / 0 - Nao): ");
            scanf("%d", &ativoInt);
            getchar();

            printf("Quantidade de Premiacoes: ");
            scanf("%d", &premios);
            getchar();

            printf("Integrantes (separados por virgula): ");
            lerString(integrantes, sizeof(integrantes));


            inserirArtista(l, genNome, nomeArt, cidade, anos, ativoInt == 1, premios, integrantes);


            Artista *artCriado = buscarArtista(l, genNome, nomeArt);


            if (artCriado != NULL){
                int qtdMusicas;
                printf("\nQuantas musicas deseja cadastrar para %s? ", nomeArt);
                scanf("%d", &qtdMusicas);
                getchar();

                for (int i = 0; i < qtdMusicas; i++) {
                    char nomeMusica[70], album[70];

                    printf("\n--- Musica %d de %d ---\n", i + 1, qtdMusicas);

                    printf("Nome da musica: ");
                    lerString(nomeMusica, sizeof(nomeMusica));

                    printf("Nome do album: ");
                    lerString(album, sizeof(album));


                    inserirMusica(artCriado, nomeMusica, album);

                }
            }
            break;
        }
        case 7:{
            char genNome[70];
            printf("Nome do Genero: ");
            lerString(genNome, sizeof(genNome));
            listarArtistas(l, genNome);
            break;
        }
        case 8:
            menuAlterarArtista(l);
            break;
        case 9:{
            char genNome[70], artNome[70];
            printf("Nome do Genero: ");
            lerString(genNome, sizeof(genNome));
            printf("Nome do Artista a remover: ");
            lerString(artNome, sizeof(artNome));
            removerArtista(l, genNome, artNome);
            break;
        }
        case 10:{
            char genNome[70];
            printf("Nome do Genero: ");
            lerString(genNome, sizeof(genNome));
            printf("\nTotal de artistas em '%s': %d\n", genNome, contarArtistas(l, genNome));
            break;
        }
        case 11:
            contabilizarArtistasPorGenero(l);
            break;
        case 12:
            buscarArtistasEmMultiplosGeneros(l);
            break;
        case 13:{
            char genNome[70];
            printf("Nome do Genero para ordenar: ");
            lerString(genNome, sizeof(genNome));
            ordenarArtistasPorNome(l, genNome);
            break;
        }
        case 14:
            gerarRelatorioGeral(l);
            break;
        case 15:
            gerarTop3Generos(l);
            break;
        case 16:{
            char genNome[70];
            int premios;
            printf("Nome do Genero: ");
            lerString(genNome, sizeof(genNome));
            printf("Quantidade minima de premios: ");
            scanf("%d", &premios);
            getchar();
            filtarNumeroPremios(l, genNome, premios);
            break;
        }
        case 0:
            printf("\nEncerrando e liberando toda a memoria...\n");
            destruirListaGeneros(l);
            printf("Programa finalizado com sucesso!\n");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n");
        }
         if (opcao != 0){
            pausar();
        }
    } while (opcao != 0);
}

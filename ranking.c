#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ranking.h"

/* Pontuação = discos * 100 * minimo / jogadas.
   Jogo perfeito (jogadas == minimo) vale discos * 100 pontos;
   quanto mais jogadas além do mínimo, menos pontos. */
int calcular_pontos(int discos, int jogadas, int minimo) {
    if (jogadas <= 0) return 0;
    return discos * 100 * minimo / jogadas;
}

No *inserir_ordenado(No *lista, const char *nome, int pontos, int discos, int jogadas) {
    No *novo = (No *) malloc(sizeof(No));         /* alocação dinâmica do nó */
    if (novo == NULL) {
        printf(">> Sem memoria para salvar a pontuacao.\n");
        return lista;
    }
    strncpy(novo->nome, nome, TAM_NOME - 1);
    novo->nome[TAM_NOME - 1] = '\0';
    novo->pontos = pontos;
    novo->discos = discos;
    novo->jogadas = jogadas;

    /* Caso 1: lista vazia ou o novo tem mais pontos que o primeiro
       -> o novo vira a cabeça da lista. */
    if (lista == NULL || pontos > lista->pontos) {
        novo->prox = lista;
        return novo;
    }

    /* Caso 2: anda até achar o nó depois do qual o novo deve entrar.
       Em empate, o mais antigo fica na frente. */
    No *atual = lista;
    while (atual->prox != NULL && atual->prox->pontos >= pontos) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;   /* novo aponta para o que vinha depois */
    atual->prox = novo;         /* anterior passa a apontar para o novo */
    return lista;
}

void mostrar_ranking(No *lista) {
    printf("\n=============== RANKING ===============\n");
    if (lista == NULL) {
        printf("Nenhuma pontuacao registrada ainda.\n");
        printf("=======================================\n");
        return;
    }
    printf("%-4s %-18s %6s %7s %7s\n", "Pos", "Jogador", "Pontos", "Discos", "Jogadas");

    int pos = 1;
    for (No *atual = lista; atual != NULL; atual = atual->prox) {   /* percorre a lista */
        printf("%-4d %-18.18s %6d %7d %7d\n",
               pos, atual->nome, atual->pontos, atual->discos, atual->jogadas);
        pos++;
    }
    printf("=======================================\n");
    printf("Total de partidas registradas: %d\n", tamanho(lista));
}

int tamanho(No *lista) {
    int cont = 0;
    for (No *atual = lista; atual != NULL; atual = atual->prox) cont++;
    return cont;
}

void liberar_lista(No *lista) {
    while (lista != NULL) {
        No *proximo = lista->prox;   /* guarda o próximo antes de liberar */
        free(lista);
        lista = proximo;
    }
}

/* Formato de cada linha do arquivo: pontos;discos;jogadas;nome */
void salvar_ranking(No *lista, const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    if (f == NULL) {
        printf(">> Nao foi possivel salvar o ranking em %s.\n", arquivo);
        return;
    }
    for (No *atual = lista; atual != NULL; atual = atual->prox) {
        fprintf(f, "%d;%d;%d;%s\n", atual->pontos, atual->discos, atual->jogadas, atual->nome);
    }
    fclose(f);
}

No *carregar_ranking(const char *arquivo) {
    No *lista = NULL;
    FILE *f = fopen(arquivo, "r");
    if (f == NULL) return NULL;   /* primeira execução: ainda não há arquivo */

    int pontos, discos, jogadas;
    char nome[TAM_NOME];
    while (fscanf(f, "%d;%d;%d;%39[^\n]\n", &pontos, &discos, &jogadas, nome) == 4) {
        lista = inserir_ordenado(lista, nome, pontos, discos, jogadas);
    }
    fclose(f);
    return lista;
}

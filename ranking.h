#ifndef RANKING_H
#define RANKING_H

#define TAM_NOME 40

/* Nó da lista simplesmente encadeada: guarda o resultado de uma partida. */
typedef struct No {
    char nome[TAM_NOME];   /* nome do jogador */
    int pontos;            /* pontuação obtida */
    int discos;            /* quantos discos tinha a partida */
    int jogadas;           /* quantas jogadas o jogador usou */
    struct No *prox;       /* próximo nó (NULL = fim da lista) */
} No;

/* Calcula a pontuação de uma partida vencida. */
int calcular_pontos(int discos, int jogadas, int minimo);

/* Cria um nó com malloc e insere na lista mantendo a ordem
   decrescente de pontos. Retorna a nova cabeça da lista. */
No *inserir_ordenado(No *lista, const char *nome, int pontos, int discos, int jogadas);

/* Percorre a lista e mostra o ranking. */
void mostrar_ranking(No *lista);

/* Conta quantos nós a lista tem. */
int tamanho(No *lista);

/* Libera todos os nós da lista (free). */
void liberar_lista(No *lista);

/* Salva a lista em arquivo de texto e carrega de volta. */
void salvar_ranking(No *lista, const char *arquivo);
No *carregar_ranking(const char *arquivo);

#endif

#include <stdio.h>

#define MAX 8

int pinos[3][MAX];   /* pinos[p][i] = tamanho do disco i do pino p (0 = base) */
int topo[3];         /* quantos discos há em cada pino */
int n;               /* total de discos */
int movimentos;      /* jogadas feitas */

/* Descarta o resto da linha digitada. */
void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Põe todos os discos no pino A, o maior embaixo. */
void iniciar(void) {
    for (int p = 0; p < 3; p++) topo[p] = 0;
    for (int i = 0; i < n; i++) pinos[0][i] = n - i;
    topo[0] = n;
    movimentos = 0;
}

void repetir(char c, int vezes) {
    for (int i = 0; i < vezes; i++) putchar(c);
}

/* Desenha os 3 pinos. Um disco de tamanho t ocupa 2*t+1 caracteres. */
void mostrar(void) {
    printf("\n");
    for (int nivel = n - 1; nivel >= 0; nivel--) {
        for (int p = 0; p < 3; p++) {
            int t = (nivel < topo[p]) ? pinos[p][nivel] : 0;
            repetir(' ', n - t);
            if (t == 0) putchar('|');
            else repetir('#', 2 * t + 1);
            repetir(' ', n - t);
            printf("  ");
        }
        printf("\n");
    }
    for (int p = 0; p < 3; p++) {
        repetir('-', n);
        putchar('A' + p);
        repetir('-', n);
        printf("  ");
    }
    printf("\n\n");
}

/* Converte 'A', 'B', 'C' (ou minúsculas) em 0, 1, 2. Retorna -1 se inválido. */
int indice(char c) {
    if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
    if (c >= 'A' && c <= 'C') return c - 'A';
    return -1;
}

/* Move o disco do topo do pino o para o pino d. Retorna 1 se foi válido. */
int mover(int o, int d) {
    if (o < 0 || d < 0) {
        printf(">> Pino invalido. Use A, B ou C.\n");
        return 0;
    }
    if (o == d) {
        printf(">> Origem e destino sao o mesmo pino.\n");
        return 0;
    }
    if (topo[o] == 0) {
        printf(">> O pino %c esta vazio.\n", 'A' + o);
        return 0;
    }
    int disco = pinos[o][topo[o] - 1];
    if (topo[d] > 0 && pinos[d][topo[d] - 1] < disco) {
        printf(">> Nao pode colocar disco maior sobre menor!\n");
        return 0;
    }
    topo[o]--;                      /* tira da origem */
    pinos[d][topo[d]] = disco;      /* coloca no destino */
    topo[d]++;
    movimentos++;
    return 1;
}

/* Vence quando todos os discos estão no pino C. */
int venceu(void) {
    return topo[2] == n;
}

/* ---------- Recursividade ---------- */

/* Mínimo de jogadas: T(n) = 2*T(n-1) + 1 */
int minimo_jogadas(int k) {
    if (k == 0) return 0;                  /* caso base */
    return 2 * minimo_jogadas(k - 1) + 1;
}

/* Move k discos de origem para destino, usando auxiliar como apoio. */
void resolver(int k, int origem, int destino, int auxiliar) {
    if (k == 0) return;                            /* caso base */

    resolver(k - 1, origem, auxiliar, destino);    /* k-1 discos: origem -> auxiliar */

    int disco = pinos[origem][topo[origem] - 1];
    mover(origem, destino);                        /* maior disco: origem -> destino */
    printf("Passo %d: mover disco %d de %c para %c\n",
           movimentos, disco, 'A' + origem, 'A' + destino);

    resolver(k - 1, auxiliar, destino, origem);    /* k-1 discos: auxiliar -> destino */
}

/* Cada turno chama o próximo. Para quando vence (retorna 1) ou sai (retorna 0). */
int turno(void) {
    mostrar();
    if (venceu()) {
        printf("Voce venceu em %d jogadas! (minimo possivel: %d)\n",
               movimentos, minimo_jogadas(n));
        return 1;
    }

    char o, d;
    printf("Jogada %d - origem (A/B/C) ou 0 para sair: ", movimentos + 1);
    if (scanf(" %c", &o) != 1 || o == '0') return 0;
    printf("destino (A/B/C): ");
    if (scanf(" %c", &d) != 1) return 0;
    limpar_buffer();

    mover(indice(o), indice(d));
    return turno();                                /* chamada recursiva */
}

/* ---------- Menu ---------- */

/* Pergunta quantos discos (3 a MAX). Retorna 0 se a entrada acabou. */
int pedir_discos(void) {
    int d = 0;
    while (d < 3 || d > MAX) {
        printf("Quantos discos (3 a %d)? ", MAX);
        if (scanf("%d", &d) == EOF) return 0;
        limpar_buffer();
    }
    return d;
}

int main(void) {
    int opcao = 0;

    while (opcao != 3) {
        printf("\n=== TORRE DE HANOI ===\n");
        printf("1 - Jogar\n2 - Ver a solucao automatica\n3 - Sair\nEscolha: ");

        int r = scanf("%d", &opcao);
        if (r == EOF) break;
        limpar_buffer();
        if (r == 0) opcao = 0;

        if (opcao == 1) {
            n = pedir_discos();
            if (n > 0) {
                iniciar();
                printf("Objetivo: levar todos os discos do pino A para o C.\n");
                printf("Minimo possivel: %d jogadas.\n", minimo_jogadas(n));
                turno();
            }
        } else if (opcao == 2) {
            n = pedir_discos();
            if (n > 0) {
                iniciar();
                mostrar();
                resolver(n, 0, 2, 1);
                mostrar();
            }
        } else if (opcao != 3) {
            printf(">> Opcao invalida.\n");
        }
    }
    return 0;
}
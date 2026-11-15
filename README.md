# Torre de Hanói — Jogo em C com Recursividade e Ranking

Trabalho da disciplina Estrutura de Dados (2026-02) — UTFPR
Curso: Tecnologia em Análise e Desenvolvimento de Sistemas

Professor: Clayton Kossoski

## Integrante

- Matheus Araujo de Oliveira — RA: 2648580

## Sobre o jogo

Jogo da Torre de Hanói. O objetivo é mover todos os discos do
pino A para o pino C, usando o pino B como apoio, sem nunca colocar um disco
maior sobre um menor.

O menu tem estas opções:

1. **Jogar** — você faz os movimentos informando o pino de origem e o de destino.
   Ao vencer, informa seu nome e a pontuação entra no ranking.
2. **Solução automática** — o programa resolve o jogo sozinho e mostra cada passo.
3. **Ver ranking** — mostra todas as pontuações, da maior para a menor.
4. **Sair**.

## Como compilar e rodar

Requisito: `gcc`.

```bash
gcc hanoi.c ranking.c -o hanoi
./hanoi
```

No Windows: `hanoi.exe`

## Como jogar

1. No menu, escolha `1` para jogar.
2. Informe o número de discos (de 3 a 8).
3. A cada jogada, digite o pino de origem (`A`, `B` ou `C`) e depois o de destino.
   Também vale digitar os dois na mesma linha, por exemplo `A C`.
4. Digite `0` na origem para encerrar a partida.
5. Ao vencer, o jogo mostra quantas jogadas você usou, o mínimo possível e a
   sua pontuação. Depois pede seu nome e mostra o ranking atualizado.

## Uso de recursividade

- `resolver()` — resolve a torre: move `k-1` discos para o pino auxiliar,
  move o maior disco para o destino e move os `k-1` discos por cima dele.
  Caso base: `k == 0`.
- `minimo_jogadas()` — calcula o mínimo de jogadas: `2 * minimo_jogadas(k-1) + 1`.
  Caso base: `k == 0`.
- `turno()` — cada jogada chama o próximo turno, até o jogador vencer ou
  digitar `0` para sair.

## Ranking com lista simplesmente encadeada

As pontuações ficam numa **lista simplesmente encadeada** implementada em
`ranking.h` / `ranking.c`. Cada nó (`struct No`) guarda o resultado de uma partida:

| Campo     | Significado                       |
|-----------|-----------------------------------|
| `nome`    | nome do jogador                   |
| `pontos`  | pontuação obtida                  |
| `discos`  | número de discos da partida       |
| `jogadas` | jogadas usadas para vencer        |
| `prox`    | ponteiro para o próximo nó        |

### Pontuação

```
pontos = discos * 100 * minimo / jogadas
```

Uma partida perfeita (no mínimo de jogadas) vale `discos * 100`. Cada jogada a
mais reduz os pontos, e partidas com mais discos valem mais.

### Operações da lista

- `inserir_ordenado()` — aloca o nó com `malloc` e o insere já na posição certa
  (ordem decrescente de pontos). Assim a lista está sempre ordenada.
- `mostrar_ranking()` — percorre a lista do início ao fim exibindo posição,
  nome, pontos, discos e jogadas.
- `tamanho()` — percorre a lista contando os nós.
- `liberar_lista()` — percorre a lista liberando cada nó com `free` (ao sair).
- `salvar_ranking()` / `carregar_ranking()` — gravam e leem a lista no arquivo
  `ranking.txt`, para o ranking não se perder ao fechar o programa.

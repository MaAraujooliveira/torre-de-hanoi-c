# Torre de Hanói — Jogo em C com Recursividade

Trabalho da disciplina Estrutura de Dados (2026-02) — UTFPR
Curso: Tecnologia em Análise e Desenvolvimento de Sistemas
Professor: Clayton Kossoski

## Integrante

- Matheus Araujo de Oliveira — RA: 2648580

## Sobre o jogo

Jogo da Torre de Hanói. O objetivo é mover todos os discos do
pino A para o pino C, usando o pino B como apoio, sem nunca colocar um disco
maior sobre um menor.

O programa tem dois modos:

1. **Jogar** — você faz os movimentos informando o pino de origem e o de destino.
2. **Solução automática** — o programa resolve o jogo sozinho e mostra cada passo.

## Como compilar e rodar

Requisito: `gcc`.

```bash
gcc hanoi.c -o hanoi
./hanoi
```

No Windows: `hanoi.exe`

## Como jogar

1. No menu, escolha `1` para jogar.
2. Informe o número de discos (de 3 a 8).
3. A cada jogada, digite o pino de origem (`A`, `B` ou `C`) e depois o de destino.
   Também vale digitar os dois na mesma linha, por exemplo `A C`.
4. Digite `0` na origem para encerrar a partida.
5. Ao vencer, o jogo mostra quantas jogadas você usou e o mínimo possível.

## Uso de recursividade

- `resolver()` — resolve a torre: move `k-1` discos para o pino auxiliar,
  move o maior disco para o destino e move os `k-1` discos por cima dele.
  Caso base: `k == 0`.
- `minimo_jogadas()` — calcula o mínimo de jogadas: `2 * minimo_jogadas(k-1) + 1`.
  Caso base: `k == 0`.
- `turno()` — cada jogada chama o próximo turno, até o jogador vencer ou
  digitar `0` para sair.
